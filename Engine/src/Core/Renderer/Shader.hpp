#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class Shader
{
  public:
    Shader()          = default;
    virtual ~Shader() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

  protected:
    uint32_t m_RendererID;
};
} // namespace Engine