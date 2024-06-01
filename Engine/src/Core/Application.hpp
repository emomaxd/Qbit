#pragma once

#include "TimeStep.hpp"

#include "Layer.hpp"

#include "LayerStack.hpp"

#include "../Renderer/Window.hpp"

int main();

namespace Qbit {
	class Application
	{
	public:
		Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application() = default;

		

		//void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		//bool OnWindowClose(WindowCloseEvent& e);
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		//ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main();
		
	};
	Application* CreateApplication();
}