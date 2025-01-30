
#include "application.h"

#include <cmath>

#include "log.h"

#include "input.h"

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include "PlatformUtils.h"

#include <filesystem>

#include "../void/Renderer.h"

#include "ScriptEngine.h"
#include <backend/Vulkan/VulkanContext.h>

namespace Qbit {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{

		QB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name)); /* Window initializes the Graphics Context. */
		m_Window->SetEventCallback(QB_BIND_EVENT_FN(Application::OnEvent));

		
		/*
		* 
		* 
		* The next scope exists only for VULKAN testing purposes,
		* when we are done with initial integration of vulkan
		* it will be gone.
		* 
		* 
		*/

		// Get the current graphics context from the window
		auto& context = m_Window->GetGraphicsContext();
		auto& vkContext = (VulkanContext&)context;

		// Proceed only if Vulkan is the active renderer API
		if (Renderer::GetAPI() == RendererAPI::API::Vulkan)
		{
			

			auto shader = Shader::Create("assets/shaders/VulkanTest.glsl");
			auto vertexArray = VertexArray::Create();


			float vertices[3 * 3 * 4] = {
				// Positions       // Colors (RGBA)
				0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,   // Top vertex (red)
			   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   // Bottom-left vertex (green)
				0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f    // Bottom-right vertex (blue)
			};

			auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position"     },
				{ ShaderDataType::Float4, "a_Color"        },
				});
			vertexArray->AddVertexBuffer(vertexBuffer);

			// Create graphics pipeline only when Vulkan context is ready
			vkContext.CreateGraphicsPipeline(shader, vertexArray);


			float colorOffset = 0.0f;

			while (true)
			{
				glfwPollEvents();

				for (int i = 0; i < 3; ++i)
				{
					float timeFactor = colorOffset * 0.2f;

					vertices[i * 7 + 3] = (sin(timeFactor + i * 0.8f) * 0.5f) + 0.5f; // R
					vertices[i * 7 + 4] = (cos(timeFactor + i * 0.6f) * 0.5f) + 0.5f; // G
					vertices[i * 7 + 5] = (sin(timeFactor + i * 0.4f) * cos(timeFactor + i * 0.7f) * 0.5f) + 0.5f; // B
				}


				colorOffset += 0.005f;

				vertexBuffer->SetData(vertices, sizeof(vertices));

				// Render the frame
				vkContext.DrawFrame(vertexArray);
			}

		}

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		ScriptEngine::Shutdown();
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(QB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(QB_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::SubmitToMainThread(const std::function<void()>& function)
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		m_MainThreadQueue.emplace_back(function);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			ExecuteMainThreadQueue();
			
			if (!m_Minimized)
			{
				{
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::ExecuteMainThreadQueue()
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		for (auto& func : m_MainThreadQueue)
			func();

		m_MainThreadQueue.clear();
	}

}