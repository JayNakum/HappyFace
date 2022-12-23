#include "ResourceManager.h"

#include <stb_image/stb_image.h>

#include <iostream>
#include <sstream>
#include <fstream>

GL::Shader ResourceManager::loadShader(const std::string& filepath) const
{
	std::string shaderSource = loadFile(filepath);

	GL::Shader::ShaderType type = GL::Shader::UNDEFINED;

	std::string ext = filepath.substr(filepath.find_first_of("."));
	if (ext == ".vs.glsl")
		type = GL::Shader::VERTEX;
	else if (ext == ".fs.glsl")
		type = GL::Shader::FRAGMENT;
	else if (ext == ".gs.glsl")
		type = GL::Shader::GEOMETRY;

	return GL::Shader(type, shaderSource);
}

GL::Texture ResourceManager::loadTexture(const std::string& dir, const std::string& path, const std::string& type) const
{
	stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
	unsigned char* data = stbi_load((dir + '/' + path).c_str(), &width, &height, &nrComponents, 0);
    
	if (!data)
	{
		std::cerr << "STB::ERROR::UNABLE TO LOAD TEXTURE" << std::endl;
		std::cerr << path << std::endl;
	}
	return GL::Texture(path, type, width, height, nrComponents, data);
}

std::string ResourceManager::loadFile(const std::string& filepath) const
{
	std::string data = "";

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filepath.c_str());
		std::stringstream dataStream;
		dataStream << file.rdbuf();
		file.close();
		data = dataStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << filepath << std::endl << e.what() << std::endl;
	}

	
	return data;
}
