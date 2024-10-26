#include "textureatlas.h"

#include <glad/glad.h>

#include "renderer.h"
#include "sprite.h"
#include "texture.h"

namespace Graphics
{

TextureAtlas::TextureAtlas(Resources::Sprite& sprite, unsigned int hDivs, unsigned int vDivs)
	: texture(new Texture(sprite)), numFrames(hDivs * vDivs),
	frameWidth(sprite.width / hDivs), frameHeight(sprite.height / vDivs),
	vaos(numFrames), vbos(numFrames), quads(numFrames)
{
	const auto& spriteWidth		{ sprite.width };
	const auto& spriteHeight	{ sprite.height };

	for (unsigned int currLine = 0; currLine < vDivs; currLine++)
	{
		for (unsigned int currCol = 0; currCol < hDivs; currCol++)
		{
			unsigned int nextVAO { }, nextVBO { };
			auto& nextQuad = quads.at((currLine + 1) * currCol);

			glGenVertexArrays(1, &nextVAO);
			glBindVertexArray(nextVAO);

			glGenBuffers(1, &nextVBO);
			glBindBuffer(GL_ARRAY_BUFFER, nextVBO);
			
			for (auto& vert : nextQuad.verts)
			{
				vert.uv = {
					(currCol + vert.uv[0]) * frameWidth / spriteWidth,
					(currLine + vert.uv[1]) * frameHeight / spriteHeight
				};
			}
			glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::verts), nextQuad.verts, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::quadEBO);

			constexpr auto stride = sizeof(Vertex);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(Vertex::position)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(Vertex::position) + sizeof(Vertex::color)));
			glEnableVertexAttribArray(2);

			vaos[(currLine + 1) * currCol] = nextVAO;
			vbos[(currLine + 1) * currCol] = nextVBO;
		}
	}
}

}