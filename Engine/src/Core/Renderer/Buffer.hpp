#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Renderer/BufferLayout.hpp"

namespace Engine
{
class VertexBuffer
{
  public:
    VertexBuffer()          = default;
    virtual ~VertexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::unique_ptr<VertexBuffer> Create(float* vertices, uint32_t size);

  public:
    inline const BufferLayout& GetLayout() const { return m_Layout; }
    inline void                SetLayout(const BufferLayout& layout) { m_Layout = layout; }

  protected:
    uint32_t     m_RendererID;
    BufferLayout m_Layout;
};

class IndexBuffer
{
  public:
    IndexBuffer()          = default;
    virtual ~IndexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

  public:
    inline uint32_t GetCount() const { return m_Count; }
    inline void     SetCount(uint32_t count) { m_Count = count; }

  protected:
    uint32_t m_RendererID;
    uint32_t m_Count;
};
} // namespace Engine