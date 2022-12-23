#include "Texture.h"

#include <stb_image/stb_image.h>

namespace GL {
    Texture::Texture(const std::string& path, const std::string& type, const int width, const int height, const int bpp, unsigned char* pixelBuffer)
        : m_width(width), m_height(height), m_nrComponents(bpp), m_format(RGBA)
    {
        this->path = path;
        this->type = type;
        glGenTextures(1, &m_id);
        switch (m_nrComponents)
        {
        case 1: m_format = Texture::R;
            break;
            //case 2: m_format = Texture::RG;
            //    break;
        case 3: m_format = Texture::RGB;
            break;
        case 4: m_format = Texture::RGBA;
            break;
        }

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, pixelBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(pixelBuffer);
    }

    void Texture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::deleteTexture() const
    {
        unbind();
        glDeleteTextures(1, &m_id);
    }
}
