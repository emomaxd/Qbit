#pragma once

#include "../../Dependencies/GLEW/include/GL/glew.h"
#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"


#include "Renderer.hpp"

class Window {
public:

	Window();

	void Cleanup();
	void Init();

	void ClearScreen();
	void SwapBuffers();
	
	void ImGuiNewFrame();
	void ImGuiRender();


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