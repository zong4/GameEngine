#pragma once

// Core
#include "Core/Events/Event.hpp"

namespace Engine
{
class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

  private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }

  private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
  public:
    MouseButtonEvent(int button) : m_Button(button) {}

  public:
    EVENT_CLASS_CATEGORY(EventCategory::MouseButton | EventCategory::Mouse | EventCategory::Input)
    inline int GetMouseButton() const { return m_Button; }

  protected:
    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(MouseButtonReleased)
};
} // namespace Engine