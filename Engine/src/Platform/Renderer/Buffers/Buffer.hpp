#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
enum class BufferUsage { Static, Dynamic, Stream };

enum class ShaderDataType { Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    default:
        Logger::EngineAssert(false, "Unknown ShaderDataType!");
        return 0;
    }
}

class Buffer
{
  public:
    virtual ~Buffer()                = default;
    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

  public:
    virtual void SetData(std::span<const std::byte> indices, uint32_t offset) = 0;

  protected:
    Buffer() = default;

  protected:
    uint32_t    m_RendererID = 0;
    BufferUsage m_Usage      = BufferUsage::Static;
};
} // namespace Engine