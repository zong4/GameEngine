#pragma once

#include "../VertexBuffer.hpp"
#include <glad/glad.h>

namespace Engine
{
class OpenGLVertexBuffer final : public VertexBuffer
{
  public:
    explicit OpenGLVertexBuffer(uint32_t size);
    explicit OpenGLVertexBuffer(std::span<const float> vertices);
    explicit OpenGLVertexBuffer(std::span<const double> vertices);
    ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
};
} // namespace Engine