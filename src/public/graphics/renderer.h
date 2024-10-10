#pragma once

#include <variant>
#include <queue>

#include <glad/glad.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "spriterenderer.h"
#include "window.h"

#include "scene.h"

namespace Graphics
{

class Texture;

class Renderer
{
public:
	Renderer(Window& window, World::Scene& scene);

	void SetClearColor(glm::vec4& clearColor);

	void EmitQuad();

	void Render();

	Texture* RegisterNewTexture();

	std::vector<SpriteRenderer> spriteRenderers;
	glm::mat4 projectionMat;

private:
	Window& window;
	World::Scene& scene;
	glm::vec4 clearColor { .2f, .3f, .3f, 1.f };
};

}