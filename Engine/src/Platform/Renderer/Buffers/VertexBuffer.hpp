#pragma once

#include "BufferLayout.hpp"

namespace Engine
{
class VertexBuffer : public Buffer
{
  public:
    virtual ~VertexBuffer() = default;

    static std::unique_ptr<VertexBuffer> Create(std::span<const float> vertices, BufferLayout layout, BufferUsage usage = BufferUsage::Static);

  public:
    const BufferLayout& GetLayout() const { return m_Layout; }
    void                SetLayout(const BufferLayout& layout) { m_Layout = layout; }

  protected:
    VertexBuffer() = default;

  protected:
    BufferLayout m_Layout;
};
} // namespace Engine