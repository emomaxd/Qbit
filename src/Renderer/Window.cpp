#include "Window.hpp"


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
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
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

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::GLFWInit(){
	if (!glfwInit())
		std::cout << "error on GLFW init" << std::endl;
	
	window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", nullptr, nullptr);

	glfwMakeContextCurrent(window);


	if (!window)
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
	glfwDestroyWindow(window);
	glfwTerminate();
}