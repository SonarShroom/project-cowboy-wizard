#pragma once

#include <variant>
#include <queue>

#include <glad/glad.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "context.h"	

#include "spriterenderer.h"
#include "window.h"

#include "scene.h"

namespace Graphics
{

class Texture;

class Renderer
{
public:
	static unsigned int quadEBO;
	glm::mat4 projectionMat;

	Renderer(Window& window, World::Scene& scene);

	void SetClearColor(glm::vec4& clearColor);

	void EmitQuad();

	void Render();

	Texture* RegisterNewTexture();

private:
	const Window& window;
	World::Scene& scene;

	Tools::Context tools { window, scene };
	glm::vec4 clearColor { .2f, .3f, .3f, 1.f };
};

}