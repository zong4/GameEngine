#pragma once

#include "Core/Renderer/Texture2D.hpp"

namespace Engine
{
class OpenGLTexture2D : public Texture2D
{
  public:
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D();

    virtual void Bind(uint32_t slot = 0) const override;
};
} // namespace Engine