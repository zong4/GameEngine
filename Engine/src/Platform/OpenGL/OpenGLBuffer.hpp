#pragma once

// Core
#include "Core/Renderer/Buffer.hpp"

namespace Engine
{
class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    void Bind() const override;
    void Unbind() const override;
};

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void Bind() const override;
    void Unbind() const override;
};
} // namespace Engine