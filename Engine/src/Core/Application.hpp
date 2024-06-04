#pragma once

#include "TimeStep.hpp"

#include "Layer.hpp"

#include "LayerStack.hpp"

#include "../Renderer/Window.hpp"

extern int main(int argc, char** argv);

namespace Qbit {

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			//HZ_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Hazel Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};



	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application() = default;

		

		//void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void Run();


	private:
		//bool OnWindowClose(WindowCloseEvent& e);

	private:
		ApplicationSpecification m_Specification;
		std::unique_ptr<Window> m_Window;
		//ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
		
	};
	Application* CreateApplication(Qbit::ApplicationCommandLineArgs args);
}