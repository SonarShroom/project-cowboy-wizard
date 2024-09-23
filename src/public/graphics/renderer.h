#pragma once

#include <glad/glad.h>
#include <glm/vec4.hpp>

#include "window.h"

namespace Graphics
{

class Renderer
{
public:
	Renderer(Window& window);

	void SetClearColor(glm::vec4& clearColor);

	void EmitQuad();

	void Render();

private:
	Window& window;
	glm::vec4 clearColor { .2f, .3f, .3f, 1.f };
};

}