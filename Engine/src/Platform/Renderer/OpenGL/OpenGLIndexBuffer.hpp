#pragma once

#include "Platform/Renderer/IndexBuffer.hpp"

namespace Engine
{
class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
};
} // namespace Engine