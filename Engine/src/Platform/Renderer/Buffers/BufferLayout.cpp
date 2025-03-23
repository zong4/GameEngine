#include "BufferLayout.hpp"

Engine::BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
    : m_Name(name), m_Type(type), m_Offset(0), m_Normalized(normalized)
{
}

uint32_t Engine::BufferElement::GetComponentCount() const
{
    switch (m_Type) {
    case ShaderDataType::Float:
        return 1;
    case ShaderDataType::Float2:
        return 2;
    case ShaderDataType::Float3:
        return 3;
    case ShaderDataType::Float4:
        return 4;
    case ShaderDataType::Mat3:
        return 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4;
    case ShaderDataType::Int:
        return 1;
    case ShaderDataType::Int2:
        return 2;
    case ShaderDataType::Int3:
        return 3;
    case ShaderDataType::Int4:
        return 4;
    case ShaderDataType::Bool:
        return 1;
    default:
        Logger::EngineAssert(false, "Unknown ShaderDataType!");
        return 0;
    }
}

void Engine::BufferLayout::CalculateOffsetsAndStride()
{
    m_Stride = 0;
    for (auto& element : m_Elements) {
        element.SetOffset(m_Stride);
        m_Stride += ShaderDataTypeSize(element.GetType());
    }
}