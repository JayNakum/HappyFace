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

GLTexture ResourceManager::loadTexture(const std::string& dir, const std::string& path, const std::string& type) const
{
	stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
	unsigned char* data = stbi_load((dir + '/' + path).c_str(), &width, &height, &nrComponents, 0);
    
	if (!data)
	{
		std::cerr << "STB::ERROR::UNABLE TO LOAD TEXTURE" << std::endl;
	}
	return GLTexture(path, type, width, height, nrComponents, data);
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
