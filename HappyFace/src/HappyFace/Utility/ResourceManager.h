#pragma once

#include "GL/Shader.h"
#include "GL/Texture.h"

#include <string>

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

	GL::Shader loadShader(const std::string& filepath) const;
	GL::Texture loadTexture(const std::string& dir, const std::string& path, const std::string& type = "texture_diffuse") const;
	std::string loadFile(const std::string& filepath) const;

};
