#pragma once

#include <core.hpp>

namespace Engine
{
class Texture
{
  public:
    virtual ~Texture() = default;

    virtual void Bind(uint32_t slot = 0) const = 0;
    virtual void Unbind() const                = 0;

  public:
    uint32_t     GetWidth() const { return m_Width; }
    uint32_t     GetHeight() const { return m_Height; }
    virtual void SetData(std::span<const uint32_t> data) = 0;

  protected:
    Texture(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}
    Texture(const std::string& path) : m_Path(path) {}

  protected:
    uint32_t    m_Width = 0, m_Height = 0;
    std::string m_Path;
    uint32_t    m_RendererID = 0;
};
} // namespace Engine