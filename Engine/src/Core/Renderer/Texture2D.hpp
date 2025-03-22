#pragma once

#include "Texture.hpp"

namespace Engine
{
class Texture2D : public Texture
{
  public:
    Texture2D(const std::string& path) : Texture(path) {}
    virtual ~Texture2D() = default;

    static std::unique_ptr<Texture2D> Create(const std::string& path);
};
} // namespace Engine