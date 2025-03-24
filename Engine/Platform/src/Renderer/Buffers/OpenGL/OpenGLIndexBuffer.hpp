#pragma once

#include "../IndexBuffer.hpp"
#include <glad/glad.h>

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