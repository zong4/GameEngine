#include "VulkanVertexArray.hpp"

static GLint ShaderDataTypeToVulkanBaseType(Engine::ShaderDataType type)
{
    switch (type) {
        case Engine::ShaderDataType::Float:
        case Engine::ShaderDataType::Float2:
        case Engine::ShaderDataType::Float3:
        case Engine::ShaderDataType::Float4:
        case Engine::ShaderDataType::Mat3:
        case Engine::ShaderDataType::Mat4:
            return GL_FLOAT;
        case Engine::ShaderDataType::Int:
        case Engine::ShaderDataType::Int2:
        case Engine::ShaderDataType::Int3:
        case Engine::ShaderDataType::Int4:
            return GL_INT;
        case Engine::ShaderDataType::Bool:
            return GL_BOOL;
        default:
            Engine::Logger::EngineAssert(false, "Unknown ShaderDataType");
            return 0;
    }
}

Engine::VulkanVertexArray::VulkanVertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);

    Logger::EngineTrace(std::format("Vulkan vertex array is constructed with ID: {0}", m_RendererID));
}

Engine::VulkanVertexArray::~VulkanVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);

    Logger::EngineTrace(std::format("Vulkan vertex array is destructed with ID: {0}", m_RendererID));
}

void Engine::VulkanVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("Vulkan error: {0}", error));
    }
}

void Engine::VulkanVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

std::vector<std::shared_ptr<Engine::VertexBuffer>> const& Engine::VulkanVertexArray::GetVertexBuffers() const
{
    return m_VertexBuffers;
}

std::shared_ptr<Engine::IndexBuffer> const& Engine::VulkanVertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

void Engine::VulkanVertexArray::AddVertexBuffer(const std::shared_ptr<Engine::VertexBuffer>& vertexBuffer)
{
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout) {
        glEnableVertexAttribArray(m_VertexBufferIndex);
        glVertexAttribPointer(m_VertexBufferIndex,
                              element.GetComponentCount(),
                              ShaderDataTypeToVulkanBaseType(element.GetType()),
                              element.GetNormalized() ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              reinterpret_cast<const void*>(static_cast<uintptr_t>(element.GetOffset())));
        m_VertexBufferIndex++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void Engine::VulkanVertexArray::SetIndexBuffer(const std::shared_ptr<Engine::IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}