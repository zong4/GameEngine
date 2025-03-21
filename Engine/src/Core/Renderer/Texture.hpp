#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class Texture
{
  public:
    Texture(const std::string& path) : m_Path(std::string(PROJECT_DIR) + "/" + path) {}
    virtual ~Texture() = default;

    virtual void Bind(uint32_t slot = 0) const = 0;
    virtual void Unbind() const                = 0;

  public:
    inline virtual uint32_t GetWidth() const { return m_Width; }
    inline virtual uint32_t GetHeight() const { return m_Height; }

  protected:
    std::string m_Path;
    uint32_t    m_Width = 0, m_Height = 0;
    uint32_t    m_RendererID = 0;
};
} // namespace Engine