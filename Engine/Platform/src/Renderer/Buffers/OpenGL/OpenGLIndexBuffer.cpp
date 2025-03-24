#include "OpenGLIndexBuffer.hpp"

Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size) : IndexBuffer(size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr,
                 GL_DYNAMIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format(
        "OpenGL index buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(std::span<uint32_t> indices)
    : IndexBuffer(static_cast<uint32_t>(indices.size()))
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(),
                 GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format(
        "OpenGL index buffer is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

    Logger::EngineTrace(std::format(
        "OpenGL index buffer is destructed with ID: {0}", m_RendererID));
}

void Engine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Engine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::OpenGLIndexBuffer::SetData(std::span<uint32_t> indices,
                                        uint32_t offset)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, indices.size_bytes(),
                    indices.data());

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineTrace(std::format(
        "OpenGL index buffer is updated with ID: {0}", m_RendererID));
}