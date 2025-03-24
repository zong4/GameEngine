#pragma once

#include "../IndexBuffer.hpp"
#include <glad/glad.h>

namespace Engine
{
class OpenGLIndexBuffer final : public IndexBuffer
{
  public:
    explicit OpenGLIndexBuffer(uint32_t size);
    explicit OpenGLIndexBuffer(std::span<uint32_t> indices);
    ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

  public:
    virtual void SetData(std::span<uint32_t> indices, uint32_t offset = 0) override;
};
} // namespace Engine