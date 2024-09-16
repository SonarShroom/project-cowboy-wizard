#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Graphics
{

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
};

struct Triangle
{
	Vertex verts[3];
};

struct Quad
{
	Vertex verts[4];
};

}