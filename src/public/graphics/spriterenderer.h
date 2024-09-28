#pragma once

#include "primitives.h"

namespace Resources
{
	class Shader;
}

namespace Graphics
{

class SpriteRenderer
{
public:
	SpriteRenderer();

	void Render();

	unsigned int vao			{ };
	unsigned int vbo			{ };
	unsigned int ebo			{ };
	Quad quad;
	Resources::Shader* shader	{ };
};

}