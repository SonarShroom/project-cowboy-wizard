#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "resource.h"
#include "font.h"
#include "sprite.h"
#include "sound.h"
#include "shader.h"

namespace Resources
{

class Texture;

class Manager
{
public:
	Manager();
	~Manager();

	template<typename T>
	T* CreateResource(const std::filesystem::path& path) { return nullptr; }

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

	FT_Library ftLibrary { };
};

template<>
Font* Manager::CreateResource(const std::filesystem::path& fontPath);

template<>
Sprite* Manager::CreateResource(const std::filesystem::path& pngPath);

template<>
Sound* Manager::CreateResource(const std::filesystem::path& soundPath);

}