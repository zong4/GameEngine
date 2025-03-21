#include "OpenGLTexture2D.hpp"

#include <glad/glad.h>
#include <stb_image.h>

Engine::OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : Texture2D(path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ENGINE_ASSERT(data, "Failed to load image: {0}", path);

    m_Width  = width;
    m_Height = height;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = 0;
    if (channels == 4) {
        format = GL_RGBA;
    }
    else if (channels == 3) {
        format = GL_RGB;
    }
    else {
        ENGINE_ASSERT(false, "Unknown image format: {0}", path);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Engine::OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_RendererID);
}

void Engine::OpenGLTexture2D::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}