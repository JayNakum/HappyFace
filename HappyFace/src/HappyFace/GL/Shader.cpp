#include "Shader.h"

#include "Utility/ResourceManager.h"

#include <iostream>

namespace GL {
	Shader::Shader(const ShaderType type, const std::string& source)
		: m_source(source), m_type(type)
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

	Shader::~Shader()
	{
		deleteShader();
	}

	void Shader::deleteShader()
	{
		glDeleteShader(m_id);
	}
}
