#include "OpenGLIndexBuffer.hpp"

Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(std::span<const uint32_t> indices, BufferUsage usage)
{
    m_Size = indices.size();

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size * sizeof(uint32_t), indices.data(), BufferUsageToOpenGLUsage(usage));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: 0x{0:x}", err));
    }

    Logger::EngineTrace(std::format("OpenGL index buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    if (m_RendererID != 0) {
        glDeleteBuffers(1, &m_RendererID);
    }

    Logger::EngineTrace(std::format("OpenGL index buffer is destructed with ID: {0}", m_RendererID));
}

void Engine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::OpenGLIndexBuffer::SetData(std::span<const std::byte> indices, uint32_t offset)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), indices.size_bytes(), indices.data());

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: 0x{0:x}", err));
    }

    Logger::EngineTrace(std::format("OpenGL index buffer is updated with ID: {0}", m_RendererID));
}