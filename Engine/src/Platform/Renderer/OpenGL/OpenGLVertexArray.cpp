#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

static GLint ShaderDataTypeToOpenGLBaseType(Engine::ShaderDataType type)
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
        Engine::Logger::EngineAssert(false, "Unknown ShaderDataType!");
        return 0;
    }
}

Engine::OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);

    Logger::EngineInfo(std::format("OpenGL vertex array is created with ID: {0}", m_RendererID));
}

Engine::OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);

    Logger::EngineInfo(std::format("OpenGL vertex array is deleted with ID: {0}", m_RendererID));
}

void Engine::OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void Engine::OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

std::vector<std::shared_ptr<Engine::VertexBuffer>> const& Engine::OpenGLVertexArray::GetVertexBuffers() const
{
    return m_VertexBuffers;
}

std::shared_ptr<Engine::IndexBuffer> const& Engine::OpenGLVertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

void Engine::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<Engine::VertexBuffer>& vertexBuffer)
{
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout) {
        glEnableVertexAttribArray(m_VertexBufferIndex);
        glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.GetType()),
                              element.GetNormalized() ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              reinterpret_cast<const void*>(static_cast<uintptr_t>(element.GetOffset())));
        m_VertexBufferIndex++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void Engine::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<Engine::IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}