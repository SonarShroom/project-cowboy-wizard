#include "animationrenderer.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "shader.h"
#include "texture.h"

namespace Graphics
{

void AnimationRenderer::Update(float dt)
{
	const auto timeToWait { 1.f / fps };
	timer += dt;
	if (timer >= timeToWait)
	{
		currAnimFrame = (currAnimFrame + 1) % atlas->numFrames;
		timer -= timeToWait;
	}
}

void AnimationRenderer::Render()
{
	if (shader)
	{
		glUseProgram(shader->shaderProg);
		shader->SetMatrix4("model", modelMatrix);
		shader->SetMatrix4("projection", renderer.projectionMat);
	}

	if (atlas)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, atlas->texture->id);

		glBindVertexArray(atlas->vaos[currAnimFrame]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

}