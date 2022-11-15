#pragma once

#include "GLShader.h"
#include "GLTexture.h"

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

	GLShader loadShader(const std::string& filepath) const;
	STBImage loadTextureImage(char const* path) const;
	std::string loadFile(const std::string& filepath) const;

};
