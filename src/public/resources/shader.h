#pragma once

#include "resource.h"

namespace Resources
{

class Shader : public Resource
{
public:
	Shader(const std::string& id, const std::string_view& vertexShader, const std::string_view& fragmentShader);
	~Shader();

	unsigned int shaderProg { };
};

}