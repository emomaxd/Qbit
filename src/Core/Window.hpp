#pragma once
#include "../../Dependencies/GLEW/include/GL/glew.h"
#include "../../Dependencies/GLFW/include/GLFW/glfw3.h"

class Window {
public:
	void init();
	inline GLFWwindow* getWindow() { return this->window; }
	void destroy();
	
private:
	void initGLFW();
	void initGLEW();

private:
	GLFWwindow* window;

};