#include "font.h"

namespace Resources
{

Font::~Font()
{
	auto err = FT_Done_Face(face);
	if (err)
	{
		spdlog::warn("Could not free font face!");
	}
}

}