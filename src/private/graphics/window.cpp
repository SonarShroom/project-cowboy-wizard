#include "window.h"

#include <stdexcept>

namespace Graphics
{

void ShouldCloseCallback(GLFWwindow* window)
{
	auto* _window = (Window*) glfwGetWindowUserPointer(window);
	_window->shouldClose = true;
}

Window::Window(
	const std::string& title,
	const int newWidth, const int newHeight,
	const PresentMode initialMode
) {
	if (glfwInit() == GLFW_FALSE)
	{
		throw std::runtime_error("Could not initialize GLFW!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	switch (initialMode)
	{
	case PresentMode::WINDOWED: {
		window = glfwCreateWindow(newWidth, newHeight, title.c_str(), nullptr, nullptr);
	} break;
	case PresentMode::FULLSCREEN: {
		window = glfwCreateWindow(newWidth, newHeight, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	} break;
	case PresentMode::BORDERLESS_FULLSCREEN: {
		auto* monitor = glfwGetPrimaryMonitor();
		const auto* mode = glfwGetVideoMode(monitor);
		
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
	} break;
	}
	
	if (!window)
	{
		throw std::runtime_error("Could not create window with GLFW!");
	}

	glfwSetWindowUserPointer(window, this);

	glfwSetWindowCloseCallback(window, &ShouldCloseCallback);

	glfwGetFramebufferSize(window, &width, &height);

	glfwMakeContextCurrent(window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

Window::~Window()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}

}