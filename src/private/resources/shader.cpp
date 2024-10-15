#include "shader.h"

#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Resources
{

Shader::Shader(const std::string& id, const std::string_view& vertexShader, const std::string_view& fragmentShader)
	: Resource(id, Type::SHADER)
{
	auto vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	auto fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertData = vertexShader.data();
	glShaderSource(vertShaderID, 1, &vertData, nullptr);
	glCompileShader(vertShaderID);

	int success { };
	char infoLog[512] { };
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShaderID, 512, nullptr, infoLog);
		glDeleteShader(vertShaderID);
		throw std::runtime_error(std::string(infoLog));
	}

	const char* fragData = fragmentShader.data();
	glShaderSource(fragShaderID, 1, &fragData, nullptr);
	glCompileShader(fragShaderID);

	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShaderID, 512, nullptr, infoLog);
		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);
		throw std::runtime_error(std::string(infoLog));
	}

	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShaderID);
	glAttachShader(shaderProg, fragShaderID);
	glLinkProgram(shaderProg);

	glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProg, 512, nullptr, infoLog);
		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);
		glDeleteProgram(shaderProg);
		throw std::runtime_error(std::string(infoLog));
	}
}

Shader::~Shader()
{
	glDeleteProgram(shaderProg);
}

void Shader::SetBool(const std::string& name, const bool val)
{
	auto loc = glGetUniformLocation(shaderProg, name.c_str());
	glUniform1i(loc, (int)val);
}

void Shader::SetInt(const std::string& name, const int val)
{
	auto loc = glGetUniformLocation(shaderProg, name.c_str());
	glUniform1i(loc, val);
}

void Shader::SetFloat(const std::string& name, const float val)
{
	auto loc = glGetUniformLocation(shaderProg, name.c_str());
	glUniform1f(loc, val);
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& mat)
{
	auto loc = glGetUniformLocation(shaderProg, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

}