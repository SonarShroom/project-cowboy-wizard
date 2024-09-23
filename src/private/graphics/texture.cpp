#include "texture.h"

#include <glad/glad.h>

namespace Graphics
{

Texture::Texture()
{
	glGenTextures(1, &apiId);
}

Texture::~Texture()
{
	glDeleteTextures(1, &apiId);
}

}