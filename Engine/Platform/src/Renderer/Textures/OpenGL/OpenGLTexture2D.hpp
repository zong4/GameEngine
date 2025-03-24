#pragma once

#include "../Texture2D.hpp"
#include <glad/glad.h>

namespace Engine
{
class OpenGLTexture2D final : public Texture2D
{
  public:
    explicit OpenGLTexture2D(uint32_t width, uint32_t height);
    explicit OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D();

    virtual void Bind(uint32_t slot = 0) const override;
    virtual void Unbind() const override;

  public:
    virtual void SetData(std::span<const uint32_t> data) override;
};
} // namespace Engine