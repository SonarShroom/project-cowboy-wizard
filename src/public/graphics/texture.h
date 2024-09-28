#pragma once

namespace Resources
{
	class Sprite;
}

namespace Graphics
{

class Texture
{
public:
	Texture();
	Texture(const Resources::Sprite& sprite);
	~Texture();

	void SetSprite(const Resources::Sprite& sprite);

	unsigned int id { };
	const Resources::Sprite* sprite { };
};

}