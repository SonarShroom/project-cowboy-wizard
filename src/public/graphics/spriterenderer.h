#pragma once

#include <glm/mat4x4.hpp>

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
	static constexpr char name[] = "Sprite Renderer";

	SpriteRenderer(Graphics::Renderer& renderer);

	void Render();

	inline const Resources::Sprite* GetSprite() { return sprite; }
	void SetSprite(const Resources::Sprite& sprite);
	inline const Texture* GetTexture() { return texture; }

	unsigned int vao				{ };
	unsigned int vbo				{ };
	unsigned int ebo				{ };
	Quad quad;
	Resources::Shader* shader		{ };
	unsigned int width				{ };
	unsigned int height				{ };
	glm::mat4 modelMatrix			{ 1.0f };

private:
	const Resources::Sprite* sprite	{ };

	Renderer& renderer;
	Texture* texture				{ };
};

}