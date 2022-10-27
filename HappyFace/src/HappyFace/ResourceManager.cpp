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

unsigned int ResourceManager::loadTexture(char const* path) const
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
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
