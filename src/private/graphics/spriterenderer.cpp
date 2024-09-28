#include "spriterenderer.h"

#include <glad/glad.h>

#include "shader.h"

namespace Graphics
{

SpriteRenderer::SpriteRenderer()
{
	constexpr auto type = GL_ARRAY_BUFFER;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sizeof(Quad::verts), quad.verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Quad::elementIndicies), Quad::elementIndicies, GL_STATIC_DRAW);

	constexpr auto stride = sizeof(Vertex);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(Vertex::position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(Vertex::position) + sizeof(Vertex::color)));
	glEnableVertexAttribArray(2);
}

void SpriteRenderer::Render()
{
	if (shader)
	{
		glUseProgram(shader->shaderProg);
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

}