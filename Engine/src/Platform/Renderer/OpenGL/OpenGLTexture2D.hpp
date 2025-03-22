#pragma once

#include "Platform/Renderer/Texture2D.hpp"

namespace Engine
{
class OpenGLTexture2D : public Texture2D
{
  public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D();

    virtual void Bind(uint32_t slot = 0) const override;
    virtual void Unbind() const override;

    virtual void SetData(void* data, uint32_t size) override;
};
} // namespace Engine