#pragma once

#include "../VertexBuffer.hpp"
#include "OpenGLBuffer.hpp"

namespace Engine
{
class OpenGLVertexBuffer final : public VertexBuffer
{
  public:
    explicit OpenGLVertexBuffer(std::span<const float> vertices, BufferLayout layout, BufferUsage usage);
    ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

  public:
    virtual void SetData(std::span<const std::byte> vertices, uint32_t offset) override;
};
} // namespace Engine