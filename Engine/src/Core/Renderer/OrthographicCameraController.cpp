#include "OrthographicCameraController.hpp"

#include "Core/Input/Input.hpp"
#include "Core/Input/KeyCodes.hpp"

Engine::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
{
}

void Engine::OrthographicCameraController::OnUpdate(Timestep timestep)
{
    if (Input::IsKeyPressed(ENGINE_KEY_W)) {
        m_CameraPosition.y += m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(ENGINE_KEY_S)) {
        m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(ENGINE_KEY_A)) {
        m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(ENGINE_KEY_D)) {
        m_CameraPosition.x += m_CameraTranslationSpeed * timestep;
    }

    m_Camera.SetPosition(m_CameraPosition);

    if (m_Rotation) {
        if (Input::IsKeyPressed(ENGINE_KEY_Q)) {
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        }
        if (Input::IsKeyPressed(ENGINE_KEY_E)) {
            m_CameraRotation -= m_CameraRotationSpeed * timestep;
        }

        m_Camera.SetRotation(m_CameraRotation);
    }

    m_CameraTranslationSpeed = m_ZoomLevel; 
}

void Engine::OrthographicCameraController::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool Engine::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
{
    m_ZoomLevel -= event.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}

bool Engine::OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
{
    m_AspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}