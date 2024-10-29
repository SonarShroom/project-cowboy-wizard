#pragma once

#include "renderer.h"

#include "textureatlas.h"

namespace Resources
{
	class Shader;
}

namespace Graphics
{

class AnimationRenderer
{
public:
	static constexpr char name[] = "Animation Renderer";

	AnimationRenderer(Renderer& renderer) : renderer(renderer) { }

	void Update(float dt);

	void Render();

	inline TextureAtlas* GetTextureAtlas() { return atlas; }
	inline void SetTextureAtlas(TextureAtlas* texAtlas) {
		atlas = texAtlas;
		currAnimFrame = 0;
		timer = 0;
		width = texAtlas->frameWidth;
		height = texAtlas->frameHeight;
	}

	unsigned int fps			{ };
	unsigned int width			{ };
	unsigned int height			{ };
	unsigned int currAnimFrame	{ };
	float timer					{ };
	Resources::Shader* shader	{ };
	glm::mat4 modelMatrix		{ 1.0f };

private:
	TextureAtlas* atlas			{ };
	Renderer& renderer;
};

}