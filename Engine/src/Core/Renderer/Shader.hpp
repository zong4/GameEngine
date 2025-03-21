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

    static std::shared_ptr<Shader> Create(const std::string& vertexFilepath, const std::string& fragmentFilepath);

  public:
    virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)             = 0;
    virtual void SetUniform4f(const std::string& name, glm::vec4 vector)                       = 0;
    virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
    virtual void SetUniform3f(const std::string& name, glm::vec3 vector)                       = 0;
    virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2)           = 0;
    virtual void SetUniform2f(const std::string& name, glm::vec2 vector)                       = 0;
    virtual void SetUniform2f(const std::string& name, float v0, float v1)                     = 0;
    virtual void SetUniform1f(const std::string& name, float value)                            = 0;
    virtual void SetUniform1i(const std::string& name, int value)                              = 0;

  protected:
    uint32_t m_RendererID = 0;
};
} // namespace Engine