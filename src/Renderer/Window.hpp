#pragma once

#include "../../Dependencies/GLEW/include/GL/glew.h"
#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"
//#include "../../Dependencies/imgui/imgui_impl_glfw.cpp"


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


	inline GLFWwindow* getWindow() { return this->window; }

private:

	void ImGuiInit();
	void GLFWInit();
	void GLEWInit();

	void ImGuiCleanup();
	void GLFWCleanup();

private:

	GLFWwindow* window;


};