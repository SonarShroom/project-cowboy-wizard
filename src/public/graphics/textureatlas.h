#pragma once

#include <vector>

#include "primitives.h"

namespace Resources
{
	class Sprite;
}

namespace Graphics
{
class Texture;

class TextureAtlas
{
public:
	TextureAtlas() = default;
	TextureAtlas(Resources::Sprite& sprite, unsigned int hDivs, unsigned int vDivs);

	Texture* texture		{ };
	unsigned int numFrames	{ };
	float frameWidth		{ };
	float frameHeight		{ };

	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<Quad> quads;
};

}