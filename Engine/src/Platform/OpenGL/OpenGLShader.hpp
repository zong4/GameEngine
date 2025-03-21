#pragma once

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

  public:
    virtual void        SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;
    inline virtual void SetUniform4f(const std::string& name, glm::vec4 vector) override { SetUniform4f(name, vector.x, vector.y, vector.z, vector.w); }
    virtual void        SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
    inline virtual void SetUniform3f(const std::string& name, glm::vec3 vector) override { SetUniform3f(name, vector.x, vector.y, vector.z); }
    virtual void        SetUniform3f(const std::string& name, float v0, float v1, float v2) override;
    inline virtual void SetUniform2f(const std::string& name, glm::vec2 vector) override { SetUniform2f(name, vector.x, vector.y); }
    virtual void        SetUniform2f(const std::string& name, float v0, float v1) override;
    virtual void        SetUniform1f(const std::string& name, float value) override;
    virtual void        SetUniform1i(const std::string& name, int value) override;
};
} // namespace Engine