#include "texture.h"

#include <glad/glad.h>
#include <png.h>

#include "sprite.h"

namespace Graphics
{

Texture::Texture()
{
	glGenTextures(1, &id);
}

Texture::Texture(const Resources::Sprite& newSprite) : Texture()
{
	SetSprite(newSprite);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::SetSprite(const Resources::Sprite& newSprite) {
	constexpr auto type { GL_TEXTURE_2D };
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(type, id);
	const auto colorType { newSprite.colorType == PNG_COLOR_TYPE_RGBA ? GL_RGBA : GL_RGB };
	glTexImage2D(
		type, 0,
		GL_RGBA, newSprite.width, newSprite.height, 0,
		colorType, GL_UNSIGNED_BYTE, newSprite.pngData.data()
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	sprite = &newSprite;
}

}