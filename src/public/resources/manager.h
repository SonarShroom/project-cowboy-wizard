#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>

#include "resource.h"
#include "sprite.h"

namespace Resources
{

class Shader;
class Texture;

class Manager
{
public:
	template<typename T>
	T* CreateResource(const std::filesystem::path& path) { return nullptr; }

	template<>
	Sprite* CreateResource<Sprite>(const std::filesystem::path& path);

	Shader* CreateDefaultShader(const std::string& id, const std::string_view& vertexShader, const std::string_view& fragShader);

	template<typename T>
	T* GetResource(const std::string& id)
	{
		for (const auto& [resId, res] : resources)
		{
			if (id == resId)
			{
				if (res->resType == T::type)
				{
					return (T*)res.get();
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	T* GetOrCreateResource(const std::string& id)
	{
		for (const auto& [resId, res] : resources)
		{
			if (id == resId)
			{
				if (res->resType == T::type)
				{
					return (T*)res.get();
				}
				else
				{
					return nullptr;
				}
			}
		}
		return CreateResource<T>(id);
	}

private:
	std::map<std::string, std::unique_ptr<Resource>> resources;
};

}