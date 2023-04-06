#pragma once

#include "GL/ShaderProgram.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

#include <string>
#include <vector>

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

	GL::ShaderProgram loadShaderProgram(const std::vector<std::string>& shaderPaths) const;
	GL::Shader loadShader(const std::string& filepath) const;
	GL::Texture loadTexture(const std::string& dir, const std::string& path, const std::string& type = "texture_diffuse") const;
	std::string loadFile(const std::string& filepath) const;
};
