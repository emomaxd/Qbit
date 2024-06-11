#pragma once

#include "TimeStep.h"

#include "Layer.h"

#include "LayerStack.h"

#include "Window.h"

#include "Qbit/Core/Base.h"

#include "Qbit/Events/ApplicationEvent.h"

#include "Qbit/ImGui/ImGuiLayer.h"

extern int main(int argc, char** argv);

namespace Qbit {

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			//QB_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Qbit Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};



	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);

	};
	Application* CreateApplication(Qbit::ApplicationCommandLineArgs args);
}