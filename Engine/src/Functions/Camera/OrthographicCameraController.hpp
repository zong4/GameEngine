#pragma once

#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/MouseEvent.hpp"
#include "Core/Timestep.hpp"
#include "Functions/Camera/OrthographicCamera.hpp"

namespace Engine
{
class OrthographicCameraController
{
  public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Timestep timestep);
    void OnEvent(Event& event);

    float GetZoomLevel() const { return m_ZoomLevel; }
    void  SetZoomLevel(float level) { m_ZoomLevel = level; }

  public:
    OrthographicCamera&       GetCamera() { return m_Camera; }
    const OrthographicCamera& GetCamera() const { return m_Camera; }

  private:
    bool OnMouseScrolled(MouseScrolledEvent& event);
    bool OnWindowResized(WindowResizeEvent& event);

  private:
    float              m_AspectRatio;
    float              m_ZoomLevel = 1.0f;
    OrthographicCamera m_Camera;
    bool               m_Rotation;

    glm::vec3 m_CameraPosition         = {0.0f, 0.0f, 0.0f};
    float     m_CameraRotation         = 0.0f; // In degrees, in the anti-clockwise direction
    float     m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};
} // namespace Engine