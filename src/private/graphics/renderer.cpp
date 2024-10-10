#include "renderer.h"

#include <stdexcept>

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	auto* _window = (Window*)glfwGetWindowUserPointer(window);
	_window->width = width;
	_window->height = height;
	glViewport(0, 0, width, height);

	_window->renderer->projectionMat = glm::ortho<float>(0, width, height, 0, -1, 1);
}

Renderer::Renderer(Window& window, World::Scene& scene) : window(window), scene(scene)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Couldn't initialize GLAD!");
	}

	glViewport(0, 0, window.width, window.height);
	projectionMat = glm::ortho<float>(0, window.width, window.height, 0, -1, 1);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glfwSetFramebufferSizeCallback(window.GetRawWindow(), &FrameBufferSizeCallback);
	window.renderer = this;
}

void Renderer::SetClearColor(glm::vec4& clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	clearColor = clearColor;
}

void Renderer::Render()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	auto rendererView = scene.registry.view<Graphics::SpriteRenderer>();
	for (auto [ent, renderer] : rendererView.each())
	{
		renderer.Render();
	}
}

}