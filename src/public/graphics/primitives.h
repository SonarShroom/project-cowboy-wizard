#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Graphics
{

struct Vertex
{
	glm::vec2 position	{ };
	glm::vec4 color		{ 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec2 uv		{ };
};

struct Triangle
{
	Vertex verts[3];
	static constexpr int elementIndicies[] = {
		0, 1, 2
	};
};

struct Quad
{
	Vertex verts[4]
	{
		{
			{ 1.f, 1.f, },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.f, 1.f },
		},
		{
			{ 1.f, 0.f, },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.f, 0.f },
		},
		{
			{ 0.f, 0.f, },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 0.f, 0.f },
		},
		{
			{ 0.f, 1.f, },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 0.f, 1.f },
		},
	};
	static constexpr int elementIndicies[] = {
		0, 1, 3,
		1, 2, 3
	};
};

}