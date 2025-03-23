#include "OpenGLIndexBuffer.hpp"

#include <glad/glad.h>

Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
{
    SetCount(count);

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    Logger::EngineTrace(std::format("OpenGL index buffer is created with ID: {0}", m_RendererID));
}

Engine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

    Logger::EngineTrace(std::format("OpenGL index buffer is deleted with ID: {0}", m_RendererID));
}

void Engine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}