#pragma once

#include <string>
#include <glad/glad.h>


class GLTexture
{
public:
    enum Format : int {
        R = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    GLTexture(
        const int width,
        const int height,
        const int bpp,
        unsigned char* pixelBuffer
    );

public:
    void bind(unsigned int slot = 0) const;
    void unbind() const;
    void deleteTexture() const;
    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }

private:
    unsigned int m_id;
    int m_width, m_height, m_nrComponents;
    Format m_format;
};