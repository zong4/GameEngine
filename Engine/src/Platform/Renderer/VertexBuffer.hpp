#pragma once

#include "Platform/Renderer/BufferLayout.hpp"

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
    const BufferLayout& GetLayout() const { return m_Layout; }
    void                SetLayout(const BufferLayout& layout) { m_Layout = layout; }

  protected:
    uint32_t     m_RendererID = 0;
    BufferLayout m_Layout;
};
} // namespace Engine