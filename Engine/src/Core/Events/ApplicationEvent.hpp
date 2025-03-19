#pragma once

// Core
#include "Core/Events/Event.hpp"

namespace Engine
{
class WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent() = default;

  public:
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }

  private:
    unsigned int m_Width, m_Height;
};

class WindowFocusEvent : public Event
{
  public:
    WindowFocusEvent() {}

  public:
    EVENT_CLASS_TYPE(WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowLostFocusEvent : public Event
{
  public:
    WindowLostFocusEvent() {}

  public:
    EVENT_CLASS_TYPE(WindowLostFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowMovedEvent : public Event
{
  public:
    WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowMovedEvent: " << m_X << ", " << m_Y;
        return ss.str();
    }

  public:
    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    inline int GetX() const { return m_X; }
    inline int GetY() const { return m_Y; }

  private:
    int m_X, m_Y;
};

class AppTickEvent : public Event
{
  public:
    AppTickEvent() {}

  public:
    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent() {}

  public:
    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event
{
  public:
    AppRenderEvent() {}

  public:
    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
} // namespace Engine