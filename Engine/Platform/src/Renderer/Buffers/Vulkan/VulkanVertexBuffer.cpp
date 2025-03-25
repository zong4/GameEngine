#include "VulkanVertexBuffer.hpp"

Engine::VulkanVertexBuffer::VulkanVertexBuffer(uint32_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); // todo

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanVertexBuffer::VulkanVertexBuffer(std::span<const float> vertices, BufferLayout layout)
    : VertexBuffer(layout)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanVertexBuffer::VulkanVertexBuffer(std::span<const double> vertices, BufferLayout layout)
    : VertexBuffer(layout)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan vertex buffer is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanVertexBuffer::~VulkanVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

    Logger::EngineTrace(std::format("Vulkan vertex buffer is destructed with ID: {0}", m_RendererID));
}

void Engine::VulkanVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }
}

void Engine::VulkanVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::VulkanVertexBuffer::SetData(std::span<const float> vertices, uint32_t offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size_bytes(), vertices.data());

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan vertex buffer is setting data with ID: {0}", m_RendererID));
}

void Engine::VulkanVertexBuffer::SetData(std::span<const double> vertices, uint32_t offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size_bytes(), vertices.data());

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan vertex buffer is setting data with ID: {0}", m_RendererID));
}