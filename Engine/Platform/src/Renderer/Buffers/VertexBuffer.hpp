#pragma once

#include "BufferLayout.hpp"

namespace Engine
{
class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::unique_ptr<VertexBuffer> Create(uint32_t size);
    static std::unique_ptr<VertexBuffer> Create(std::span<const float> vertices);
    static std::unique_ptr<VertexBuffer> Create(std::span<const double> vertices);

  public:
    const BufferLayout& GetLayout() const { return m_Layout; }
    void                SetLayout(const BufferLayout& layout) { m_Layout = layout; }
    virtual void        SetData(std::span<const float> vertices, uint32_t offset = 0)  = 0;
    virtual void        SetData(std::span<const double> vertices, uint32_t offset = 0) = 0;

  protected:
    VertexBuffer() = default;

  protected:
    uint32_t     m_RendererID = 0;
    BufferLayout m_Layout;
};
} // namespace Engine