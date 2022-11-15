#include "GLTexture.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

GLTexture::GLTexture()
{
    glGenTextures(1, &m_id);
}

void GLTexture::init(const STBImage& texture)
{
    m_width = texture.width;
    m_height = texture.height;
    m_nrComponents = texture.bpp;

    switch (m_nrComponents)
    {
    case 1: m_format = GLTexture::R;
        break;
        //case 2: m_format = GLTexture::RG;
        //    break;
    case 3: m_format = GLTexture::RGB;
        break;
    case 4: m_format = GLTexture::RGBA;
        break;
    }

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, texture.pixelBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(texture.pixelBuffer);
}

void GLTexture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void GLTexture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::deleteTexture() const
{
    unbind();
    glDeleteTextures(1, &m_id);
}
