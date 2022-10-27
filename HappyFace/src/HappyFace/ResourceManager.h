#pragma once

#include <string>
#include <filesystem>

class ResourceManager
{
	ResourceManager() = default;
	~ResourceManager() = default;

public:
	static ResourceManager& getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	std::string loadFile(const std::filesystem::path& path) const;

};
