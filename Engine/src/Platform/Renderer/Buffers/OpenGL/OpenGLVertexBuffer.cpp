#include "OpenGLVertexBuffer.hpp"

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(std::span<const float> vertices, BufferLayout layout, BufferUsage usage)
{
    m_Layout = layout;

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), BufferUsageToOpenGLUsage(usage));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: 0x{0:x}", err));
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    if (m_RendererID != 0) {
        glDeleteBuffers(1, &m_RendererID);
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is destructed with ID: {0}", m_RendererID));
}

void Engine::OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::OpenGLVertexBuffer::SetData(std::span<const std::byte> vertices, uint32_t offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), vertices.size_bytes(), vertices.data());

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: 0x{0:x}", err));
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is updated with ID: {0}", m_RendererID));
}