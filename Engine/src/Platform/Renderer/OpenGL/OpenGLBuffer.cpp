#include "OpenGLBuffer.hpp"
#include "Platform/Renderer/Buffer.hpp"

// Platform
#include <glad/glad.h>

Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : VertexBuffer(vertices, size)
{
    glCreateBuffers(1, &m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Engine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void Engine::OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : IndexBuffer(indices, count)
{
    glCreateBuffers(1, &m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Engine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void Engine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}