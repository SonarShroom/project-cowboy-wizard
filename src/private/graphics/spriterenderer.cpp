#include "spriterenderer.h"

#include <glad/glad.h>

namespace Graphics
{

SpriteRenderer::SpriteRenderer()
{
	constexpr auto type = GL_ARRAY_BUFFER;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sizeof(Quad), quad.verts, GL_DYNAMIC_DRAW);

	constexpr auto stride = sizeof(Vertex);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	glEnableVertexAttribArray(2);
}

}