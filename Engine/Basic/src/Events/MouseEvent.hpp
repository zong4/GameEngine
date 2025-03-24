#pragma once

#include "Event.hpp"

namespace Engine
{
class MouseMovedEvent : public EventBase<EventType::MouseMoved, EventCategory::Mouse | EventCategory::Input>
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
    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

  private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public EventBase<EventType::MouseScrolled, EventCategory::Mouse | EventCategory::Input>
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

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
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

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

  private:
    int m_Button;
};
} // namespace Engine