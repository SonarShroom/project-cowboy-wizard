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

	unsigned int vao			{ };
	unsigned int vbo			{ };
	Quad quad;
	Resources::Shader* shader	{ };
};

}