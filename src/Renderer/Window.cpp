#include "Window.hpp"

namespace EMax3D{

	int Window::s_WindowWidth = 1600;
	int Window::s_WindowHeight = 900;

	float Window::s_ViewportWidth = 1600;
	float Window::s_ViewportHeight = 900;

	float Window::s_ViewportMinX = 0;
	float Window::s_ViewportMinY = 0;

	float Window::s_Red = 0.0f, Window::s_Green = 0.0f, Window::s_Blue = 0.0f, Window::s_Alpha = 1.0f;

	Window::Window() {
		Init();	
	}

	void Window::Cleanup(){
		GLFWCleanup();
		ImGuiCleanup();
	}

	void Window::Init() {
		GLFWInit();
		GLEWInit();
		ImGuiInit();
	}


	void Window::ClearScreen() {
		glViewport(s_ViewportMinX, s_ViewportMinY, s_ViewportWidth, s_ViewportHeight);
		glClearColor(s_Red, s_Green, s_Blue, s_Alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::ImGuiNewFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Window::ImGuiRender() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void Window::ImGuiInit(){

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void Window::GLFWInit(){
		if (!glfwInit())
			std::cout << "error on GLFW init" << std::endl;
		
		m_Window = glfwCreateWindow(s_WindowWidth, s_WindowHeight, "Engine", nullptr, nullptr);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwMakeContextCurrent(m_Window);


		if (!m_Window)
			std::cout << "window creation failed!" << std::endl;
	}

	void Window::GLEWInit(){
		if (glewInit() != GLEW_OK)
			std::cout << "error on GLEW init" << std::endl;
	}



	void Window::ImGuiCleanup(){
		ImGui::DestroyContext();

	}

	void Window::GLFWCleanup(){
		std::cout << "GLFW CLEANUP\n";
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

}