#include "sprite.h"

namespace Resources
{

Sprite::Sprite(const std::string ID, const std::filesystem::path pngPath) : Resource(ID)
{
	resType = Type::SPRITE;
}

}