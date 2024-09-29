#pragma once

#include <variant>
#include <queue>

#include <glad/glad.h>
#include <glm/vec4.hpp>

#include "spriterenderer.h"
#include "window.h"

namespace Graphics
{

class Texture;

class Renderer
{
public:
	Renderer(Window& window);

	void SetClearColor(glm::vec4& clearColor);

	void EmitQuad();

	void Render();

	Texture* RegisterNewTexture();

	std::vector<SpriteRenderer> spriteRenderers;

private:
	Window& window;
	glm::vec4 clearColor { .2f, .3f, .3f, 1.f };
};

}