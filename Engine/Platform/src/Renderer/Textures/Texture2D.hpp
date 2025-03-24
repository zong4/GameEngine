#pragma once

#include "Texture.hpp"

namespace Engine
{
class Texture2D : public Texture
{
  public:
    virtual ~Texture2D() = default;

    static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);
    static std::shared_ptr<Texture2D> Create(const std::string& path);

  protected:
    Texture2D(const std::string& path) : Texture(path) {}
    Texture2D(uint32_t width, uint32_t height) : Texture(width, height) {}
};
} // namespace Engine