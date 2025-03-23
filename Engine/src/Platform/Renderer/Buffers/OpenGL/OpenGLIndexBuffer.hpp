#pragma once

#include "../IndexBuffer.hpp"
#include "OpenGLBuffer.hpp"

namespace Engine
{
class OpenGLIndexBuffer final : public IndexBuffer
{
  public:
    explicit OpenGLIndexBuffer(std::span<const uint32_t> indices, BufferUsage usage);
    ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

  public:
    virtual void SetData(std::span<const std::byte> indices, uint32_t offset) override;
};
} // namespace Engine