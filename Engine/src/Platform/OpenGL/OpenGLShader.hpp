#pragma once

// Core
#include "Core/Renderer/Shader.hpp"

namespace Engine
{
class OpenGLShader : public Shader
{
  public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;
};
} // namespace Engine