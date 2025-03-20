#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class OrthographicCamera
{
  public:
    OrthographicCamera(float left, float right, float bottom, float top);

  public:
    inline const glm::vec3& GetPosition() const { return m_Position; }
    inline float            GetRotation() const { return m_Rotation; }
    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    void                    SetPosition(const glm::vec3& position);
    void                    SetRotation(float rotation);
    void                    SetProjection(float left, float right, float bottom, float top);

  private:
    void RecalculateViewMatrix();

  private:
    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    float     m_Rotation = 0.0f;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
};
} // namespace Engine