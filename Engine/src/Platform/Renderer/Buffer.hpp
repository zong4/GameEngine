#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class VertexBuffer
{
  public:
    VertexBuffer(float* vertices, uint32_t size) {}
    virtual ~VertexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

  protected:
    uint32_t m_RendererID;
};

class IndexBuffer
{
  public:
    IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {}
    virtual ~IndexBuffer() = default;

    uint32_t GetCount() const { return m_Count; }

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

  protected:
    uint32_t m_RendererID;
    uint32_t m_Count;
};
} // namespace Engine