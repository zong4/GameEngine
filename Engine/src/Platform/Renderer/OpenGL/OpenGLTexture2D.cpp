#include "OpenGLTexture2D.hpp"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Engine::OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : Texture2D(width, height)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error after texture creation: 0x{0:x}", err));
    }
}

Engine::OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : Texture2D(path)
{
    std::ifstream file(m_Path);
    Logger::EngineAssert(file.is_open(), std::format("Failed to open image: {0}", m_Path));

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
    Logger::EngineAssert(data, std::format("Failed to load image: {0}", m_Path));

    m_Width  = width;
    m_Height = height;

    GLenum internalFormat = 0, format = 0;
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        format         = GL_RGBA;
    }
    else if (channels == 3) {
        internalFormat = GL_RGB8;
        format         = GL_RGB;
    }
    else {
        Logger::EngineAssert(false,std::format("Unknown image format: {0}", m_Path));
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Fix RGB/RGBA alignment issue on OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    stbi_image_free(data);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false,std::format("OpenGL error after texture creation: 0x{0:x}", err));
    }
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

void Engine::OpenGLTexture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::OpenGLTexture2D::SetData(void* data, uint32_t size)
{
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}