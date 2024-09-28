#include "renderer.h"

#include <stdexcept>

namespace Graphics
{

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	auto* _window = (Window*)glfwGetWindowUserPointer(window);
	_window->width = width;
	_window->height = height;
	glViewport(0, 0, width, height);
}

Renderer::Renderer(Window& window) : window(window)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Couldn't initialize GLAD!");
	}

	glViewport(0, 0, window.width, window.height);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glfwSetFramebufferSizeCallback(window.GetRawWindow(), &FrameBufferSizeCallback);
}

void Renderer::SetClearColor(glm::vec4& clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	clearColor = clearColor;
}

void Renderer::Render()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& renderer : spriteRenderers)
	{
		renderer.Render();
	}
}

}