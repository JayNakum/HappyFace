#pragma once

#include <glad/glad.h>

#include <string>

namespace GL {
    class Shader
    {
    public:
        enum ShaderType : int {
            UNDEFINED = -1,
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER
        };

        Shader(const ShaderType type, const std::string& source);
        ~Shader();

        inline unsigned int getID() const { return m_id; }
        inline ShaderType getType() const { return m_type; }
        inline std::string getSourceCode() const { return m_source; }

        void deleteShader();

    private:
        unsigned int m_id{ 0 };
        std::string m_source;
        ShaderType m_type;
    };
}
