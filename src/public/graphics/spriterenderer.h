#pragma once

#include "primitives.h"

namespace Resources
{

class Shader;
class Sprite;

}

namespace Graphics
{

class Renderer;
class Texture;

class SpriteRenderer
{
public:
	SpriteRenderer(Graphics::Renderer& renderer);

	void Render();

	void SetSprite(const Resources::Sprite& sprite);

	unsigned int vao			{ };
	unsigned int vbo			{ };
	unsigned int ebo			{ };
	Quad quad;
	Resources::Shader* shader	{ };

private:
	Resources::Sprite* sprite	{ };

	Graphics::Renderer& renderer;
	Graphics::Texture* texture	{ };
};

}