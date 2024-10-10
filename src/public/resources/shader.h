#pragma once

#include "resource.h"

#include <glm/mat4x4.hpp>

namespace Resources
{

class Shader : public Resource
{
public:
	static constexpr auto type { Type::SHADER };

	Shader(const std::string& id, const std::string_view& vertexShader, const std::string_view& fragmentShader);
	~Shader();

	void SetBool(const std::string& name, const bool val);
	void SetInt(const std::string& name, const int val);
	void SetFloat(const std::string& name, const float val);
	void SetMatrix4(const std::string& name, const glm::mat4& mat);

	unsigned int shaderProg { };
};

}