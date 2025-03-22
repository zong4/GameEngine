#pragma once

#include "Core/Events/Event.hpp"

namespace Engine
{
class MouseMovedEvent : public EventBase<EventType::MouseMoved, EventCategory::Mouse | EventCategory::Input>
{
  public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        sv = ss.str();
        return sv;
    }

  public:
    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

  private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public EventBase<EventType::MouseScrolled, EventCategory::Mouse | EventCategory::Input>
{
  public:
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        sv = ss.str();
        return sv;
    }

  public:
    float GetXOffset() const { return m_XOffset; }
    float GetYOffset() const { return m_YOffset; }

  private:
    float m_XOffset, m_YOffset;
};

// class MouseButtonEvent : public EventBase<EventType::MouseButton, EventCategory::MouseButton | EventCategory::Mouse | EventCategory::Input>
// {
//   public:
//     MouseButtonEvent(int button) : m_Button(button) {}

//   public:
//     int GetMouseButton() const { return m_Button; }

//   protected:
//     int m_Button;
// };

class MouseButtonPressedEvent : public EventBase<EventType::MouseButtonPressed, EventCategory::MouseButton | EventCategory::Mouse | EventCategory::Input>
{
  public:
    MouseButtonPressedEvent(int button) : m_Button(button) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        sv = ss.str();
        return sv;
    }

  public:
    int GetMouseButton() const { return m_Button; }

  private:
    int m_Button;
};

class MouseButtonReleasedEvent : public EventBase<EventType::MouseButtonReleased, EventCategory::MouseButton | EventCategory::Mouse | EventCategory::Input>
{
  public:
    MouseButtonReleasedEvent(int button) : m_Button(button) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        sv = ss.str();
        return sv;
    }

  private:
    int m_Button;
};
} // namespace Engine