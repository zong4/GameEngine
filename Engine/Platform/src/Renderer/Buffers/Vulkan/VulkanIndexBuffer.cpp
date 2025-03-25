#include "VulkanIndexBuffer.hpp"

Engine::VulkanIndexBuffer::VulkanIndexBuffer(uint32_t size) : IndexBuffer(size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan index buffer is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanIndexBuffer::VulkanIndexBuffer(std::span<uint32_t> indices)
    : IndexBuffer(static_cast<uint32_t>(indices.size()))
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan index buffer is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanIndexBuffer::~VulkanIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

    Logger::EngineTrace(std::format("Vulkan index buffer is destructed with ID: {0}", m_RendererID));
}

void Engine::VulkanIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }
}

void Engine::VulkanIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::VulkanIndexBuffer::SetData(std::span<uint32_t> indices, uint32_t offset)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, indices.size_bytes(), indices.data());

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }

    Logger::EngineTrace(std::format("Vulkan index buffer is updated with ID: {0}", m_RendererID));
}