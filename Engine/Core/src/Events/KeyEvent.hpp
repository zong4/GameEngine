#pragma once

#include "Event.hpp"

namespace Engine {
// class KeyEvent : public EventBase<EventType::None, EventCategory::Keyboard |
// EventCategory::Input>
// {
//   public:
//     KeyEvent(int keycode) : m_KeyCode(keycode) {}

//   public:
//     int GetKeyCode() const { return m_KeyCode; }

//   protected:
//     int m_KeyCode;
// };

class KeyPressedEvent : public EventBase<EventType::KeyPressed, EventCategory::Keyboard | EventCategory::Input>
{
public:
    KeyPressedEvent(int keycode, int repeatCount) : m_KeyCode(keycode), m_RepeatCount(repeatCount) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }

public:
    int GetKeyCode() const { return m_KeyCode; }
    int GetRepeatCount() const { return m_RepeatCount; }

private:
    int m_KeyCode;
    int m_RepeatCount;
};

class KeyReleasedEvent : public EventBase<EventType::KeyReleased, EventCategory::Keyboard | EventCategory::Input>
{
public:
    KeyReleasedEvent(int keycode) : m_KeyCode(keycode) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }

public:
    int GetKeyCode() const { return m_KeyCode; }

private:
    int m_KeyCode;
};

class KeyTypedEvent : public EventBase<EventType::KeyTyped, EventCategory::Keyboard | EventCategory::Input>
{
public:
    KeyTypedEvent(int keycode) : m_KeyCode(keycode) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }

public:
    int GetKeyCode() const { return m_KeyCode; }

private:
    int m_KeyCode;
};
} // namespace Engine