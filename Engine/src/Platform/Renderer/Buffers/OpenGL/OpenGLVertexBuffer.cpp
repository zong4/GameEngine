#include "OpenGLVertexBuffer.hpp"

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    Logger::EngineTrace(std::format("OpenGL vertex buffer is created with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

    Logger::EngineTrace(std::format("OpenGL vertex buffer is deleted with ID: {0}", m_RendererID));
}

void Engine::OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}