#pragma once

#include "renderer.h"

namespace Resources
{
	class Shader;
}

namespace Graphics
{

class TextureAtlas;

class AnimationRenderer
{
public:
	AnimationRenderer(Renderer& renderer) : renderer(renderer) { }

	void Update(float dt);

	void Render();

	inline TextureAtlas* GetTextureAtlas() { return atlas; }
	inline void SetTextureAtlas(TextureAtlas* texAtlas) { atlas = texAtlas; currAnimFrame = 0; timer = 0; }

	unsigned int fps			{ };
	unsigned int currAnimFrame	{ };
	float timer					{ };
	Resources::Shader* shader	{ };
	glm::mat4 modelMatrix		{ 1.0f };

private:
	TextureAtlas* atlas			{ };
	Renderer& renderer;
};

}