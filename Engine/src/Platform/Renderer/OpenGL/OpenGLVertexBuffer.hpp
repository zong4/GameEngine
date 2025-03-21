#pragma once

#include "Platform/Renderer/VertexBuffer.hpp"

namespace Engine
{
class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
};
} // namespace Engine