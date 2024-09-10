#include "window.h"



namespace Graphics
{

std::unique_ptr<Window> Window::CreateWindow(
	const std::string& title,
	const int width, const int height
)
{
	if (glfwInit() == GLFW_FALSE)
	{
		return nullptr;
	}

	auto* glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!glfwWindow)
	{
		return nullptr;
	}
	
	return std::unique_ptr<Window>(new Window(title, width, height, glfwWindow));
}

void Window::Loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

Window::~Window() {
	glfwTerminate();
}

}