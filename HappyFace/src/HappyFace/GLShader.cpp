#include "GLShader.h"

#include "ResourceManager.h"

GLShader::GLShader(const ShaderType type, const char* sourcePath)
	: m_source(ResourceManager::getInstance().loadFile(sourcePath)), m_type(type)
{
	m_id = glCreateShader(m_type);

	const char* src = m_source.c_str();
	glShaderSource(m_id, 1, &src, NULL);
	
	glCompileShader(m_id);
	int success;
	char infoLog[1024];
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_id, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << m_type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
}

GLShader::~GLShader()
{
	deleteShader();
}

void GLShader::deleteShader()
{
	glDeleteShader(m_id);
}
