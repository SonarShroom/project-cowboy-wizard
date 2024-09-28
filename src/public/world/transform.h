#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace World
{

struct Transform
{
	glm::vec2 position;
	glm::vec3 rotation;
	glm::vec2 scale;
};

}