#pragma once

#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "Renderer.hpp"

namespace EMax3D{

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "engine",
						uint32_t width = 1280,
						uint32_t height = 720)
				: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window {
	public:

		Window();

		void Cleanup();
		void Init();

		void ClearScreen();
		void SwapBuffers();
		
		void ImGuiNewFrame();
		void ImGuiRender();

		//static Window* Create(const WindowProps& props = WindowProps());


		inline GLFWwindow* GetWindow() { return m_Window; }

		/// Variables below are static because of ease of sharing

		static int s_WindowWidth;
		static int s_WindowHeight;

		static float s_ViewportWidth;
		static float s_ViewportHeight;

		static float s_ViewportMinX; /// The position of the left edge of the viewport
		static float s_ViewportMinY; /// The position of the bottom edge of the viewport

		static float s_Red, s_Green, s_Blue, s_Alpha; /// For the clear color values

	private:

		void ImGuiInit();
		void GLFWInit();
		void GLEWInit();

		void ImGuiCleanup();
		void GLFWCleanup();

	private:

		GLFWwindow* m_Window;
		


	};

}