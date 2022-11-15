#pragma once

#include <string>
#include <glad/glad.h>

struct STBImage {
    int width;
    int height;
    int bpp;
    unsigned char* pixelBuffer;
};

class GLTexture
{
public:
    enum Format : int {
        R = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    GLTexture();

public:
    void init(const STBImage& texture);
    void bind(unsigned int slot = 0) const;
    void unbind() const;
    void deleteTexture() const;
    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }

private:
    unsigned int m_id = 0;
    int m_width = 0, m_height = 0, m_nrComponents = 0;
    Format m_format = RGBA;
};
