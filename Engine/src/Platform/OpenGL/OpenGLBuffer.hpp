#pragma once

// Core
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/BufferLayout.hpp"

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

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
};
} // namespace Engine