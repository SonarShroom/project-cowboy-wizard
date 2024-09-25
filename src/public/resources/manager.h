#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>

#include "resource.h"

namespace Resources
{

class Sprite;
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
	T* GetResource(const std::filesystem::path& path)
	{
		for (const auto& res : resources)
		{
			if (path == res->path && res->resType == T::type)
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
	}

	template<typename T>
	T* GetOrCreateResource(const std::filesystem::path& path)
	{
		for (const auto& res : resources)
		{
			if (path == res->path && res->resType == T::type)
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
		return CreateResource<T>(path);
	}

private:
	std::map<std::string, std::unique_ptr<Resource>> resources;
};

}