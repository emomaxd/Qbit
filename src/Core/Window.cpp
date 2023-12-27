#include "Window.hpp"
#include <iostream>

const static int WIDTH = 800;
const static int HEIGHT = 800;


void Window::initGLEW() {
	if (glewInit() != GLEW_OK)
		std::cout << "error on GLEW init" << std::endl;
}

void Window::initGLFW() {
	if (!glfwInit())
		std::cout << "error on GLFW init" << std::endl;


	window = glfwCreateWindow(WIDTH, HEIGHT, "Game Engine", nullptr, nullptr);

	if (!window)
		std::cout << "window creation failed!" << std::endl;

	glfwMakeContextCurrent(window);
	
}

void Window::init() {
	initGLFW();
	initGLEW();
}

void Window::destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
}