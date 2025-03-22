#pragma once

#include "Core/Events/Event.hpp"

namespace Engine
{
class WindowCloseEvent : public EventBase<EventType::WindowClose, EventCategory::Application>
{
  public:
    WindowCloseEvent() = default;
};

class WindowResizeEvent : public EventBase<EventType::WindowResize, EventCategory::Application>
{
  public:
    WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        sv = ss.str();
        return sv;
    }

  public:
    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }

  private:
    unsigned int m_Width, m_Height;
};

class WindowFocusEvent : public EventBase<EventType::WindowFocus, EventCategory::Application>
{
  public:
    WindowFocusEvent() = default;
};

class WindowLostFocusEvent : public EventBase<EventType::WindowLostFocus, EventCategory::Application>
{
  public:
    WindowLostFocusEvent() = default;
};

class WindowMovedEvent : public EventBase<EventType::WindowMoved, EventCategory::Application>
{
  public:
    WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}

    std::string_view ToString() const override
    {
        std::string_view  sv;
        std::stringstream ss;
        ss << "WindowMovedEvent: " << m_X << ", " << m_Y;
        sv = ss.str();
        return sv;
    }

  public:
    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

  private:
    int m_X, m_Y;
};

class AppTickEvent : public EventBase<EventType::AppTick, EventCategory::Application>
{
  public:
    AppTickEvent() = default;
};

class AppUpdateEvent : public EventBase<EventType::AppUpdate, EventCategory::Application>
{
  public:
    AppUpdateEvent() = default;
};

class AppRenderEvent : public EventBase<EventType::AppRender, EventCategory::Application>
{
  public:
    AppRenderEvent() = default;
};
} // namespace Engine