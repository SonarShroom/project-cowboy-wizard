#pragma once

#include "resource.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Resources
{

class Font : public Resource
{
public:
	static constexpr Type type = Type::FONT;

	Font(const std::filesystem::path path, FT_Face& face) :
		Resource(path.string(), Type::FONT),
		face(face) { }
	~Font();

	FT_Face face { };
};

}