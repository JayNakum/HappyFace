#pragma once

#include <glad/glad.h>

#include <string>

namespace GL {
    class Texture
    {
    public:
        enum Format : int {
            R = GL_RED,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA
        };

        Texture(
            const std::string& path,
            const std::string& type,
            const int width,
            const int height,
            const int bpp,
            unsigned char* pixelBuffer
        );

        std::string path;
        std::string type;

    public:
        void bind(unsigned int slot = 0) const;
        void unbind() const;
        void deleteTexture() const;
        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }

    private:
        unsigned int m_id = 0;
        int m_width, m_height, m_nrComponents;
        Format m_format;
    };
}
