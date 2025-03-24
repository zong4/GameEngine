#pragma once

#include "Event.hpp"

namespace Engine
{
class WindowCloseEvent
    : public EventBase<EventType::WindowClose, EventCategory::Application>
{
public:
    WindowCloseEvent() = default;
};

class WindowResizeEvent
    : public EventBase<EventType::WindowResize, EventCategory::Application>
{
public:
    WindowResizeEvent(std::size_t width, std::size_t height)
        : m_Width(width), m_Height(height)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

public:
    std::size_t GetWidth() const { return m_Width; }
    std::size_t GetHeight() const { return m_Height; }

private:
    std::size_t m_Width, m_Height;
};

class WindowFocusEvent
    : public EventBase<EventType::WindowFocus, EventCategory::Application>
{
public:
    WindowFocusEvent() = default;
};

class WindowLostFocusEvent
    : public EventBase<EventType::WindowLostFocus, EventCategory::Application>
{
public:
    WindowLostFocusEvent() = default;
};

class WindowMovedEvent
    : public EventBase<EventType::WindowMoved, EventCategory::Application>
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
    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

private:
    int m_X, m_Y;
};
} // namespace Engine