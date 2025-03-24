#include "OpenGLVertexBuffer.hpp"

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); // todo

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(std::span<const float> vertices)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(std::span<const double> vertices)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format("OpenGL vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

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