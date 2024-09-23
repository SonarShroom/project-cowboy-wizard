#pragma once

#include "resource.h"

namespace Graphics
{

class Texture
{
public:
	Texture();
	~Texture();

	unsigned int apiId { };
};

}