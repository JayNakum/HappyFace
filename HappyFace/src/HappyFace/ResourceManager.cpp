#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image/stb_image.h>

GLShader ResourceManager::loadShader(const std::string& filepath) const
{
	std::string shaderSource = loadFile(filepath);

	GLShader::ShaderType type = GLShader::UNDEFINED;

	std::string ext = filepath.substr(filepath.find_first_of("."));
	if (ext == ".vs.glsl")
		type = GLShader::VERTEX;
	else if (ext == ".fs.glsl")
		type = GLShader::FRAGMENT;
	else if (ext == ".gs.glsl")
		type = GLShader::GEOMETRY;

	return GLShader(type, shaderSource);
}

STBImage ResourceManager::loadTextureImage(char const* path) const
{
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	
	if (!data) std::cerr << "Failed to load TEXTURE: " << path << std::endl;

	return {width, height, nrComponents, data};
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
