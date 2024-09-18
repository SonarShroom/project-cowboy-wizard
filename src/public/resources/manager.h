#pragma once

#include <filesystem>
#include <set>

#include "resource.h"

namespace Resources
{

class Sprite;

class Manager
{
public:
	template<typename T>
	T* CreateResource(const std::filesystem::path& path) { return nullptr; }

	template<>
	Sprite* CreateResource<Sprite>(const std::filesystem::path& path);

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
	std::set<std::unique_ptr<Resource>> resources;
};

}