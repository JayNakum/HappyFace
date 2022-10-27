#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

class GLShader
{
public:
    enum ShaderType : int {
        UNDEFINED = -1,
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

    GLShader(const ShaderType type, const std::string& source);
    ~GLShader();

    inline unsigned int getID() const { return m_id; }
    inline ShaderType getType() const { return m_type; }
    inline std::string getSourceCode() const { return m_source; }

    void deleteShader();

private:
    unsigned int m_id{0};
    std::string m_source;
    ShaderType m_type;
};
#endif