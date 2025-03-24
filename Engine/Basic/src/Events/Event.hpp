#pragma once

#include "../Logger/Logger.hpp"

namespace Engine
{
enum class EventType {
    None = 0,
    AppTick,
    AppUpdate,
    AppRender,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

constexpr std::string EventTypeToString(EventType type)
{
    switch (type) {
    case EventType::None:
        return "None";
    case EventType::AppTick:
        return "AppTick";
    case EventType::AppUpdate:
        return "AppUpdate";
    case EventType::AppRender:
        return "AppRender";
    case EventType::WindowClose:
        return "WindowClose";
    case EventType::WindowResize:
        return "WindowResize";
    case EventType::WindowFocus:
        return "WindowFocus";
    case EventType::WindowLostFocus:
        return "WindowLostFocus";
    case EventType::WindowMoved:
        return "WindowMoved";
    case EventType::KeyPressed:
        return "KeyPressed";
    case EventType::KeyReleased:
        return "KeyReleased";
    case EventType::KeyTyped:
        return "KeyTyped";
    case EventType::MouseButtonPressed:
        return "MouseButtonPressed";
    case EventType::MouseButtonReleased:
        return "MouseButtonReleased";
    case EventType::MouseMoved:
        return "MouseMoved";
    case EventType::MouseScrolled:
        return "MouseScrolled";
    default:
        Logger::EngineAssert(false, "Unknown event type!");
        return "";
    }
}

enum class EventCategory { None = 0, Application = 1 << 0, Input = 1 << 1, Keyboard = 1 << 2, Mouse = 1 << 3, MouseButton = 1 << 4 };

constexpr EventCategory operator|(EventCategory lhs, EventCategory rhs) noexcept
{
    return static_cast<EventCategory>(static_cast<std::underlying_type_t<EventCategory>>(lhs) | static_cast<std::underlying_type_t<EventCategory>>(rhs));
}

constexpr bool operator&(EventCategory lhs, EventCategory rhs) noexcept
{
    return (static_cast<std::underlying_type_t<EventCategory>>(lhs) & static_cast<std::underlying_type_t<EventCategory>>(rhs)) != 0;
}

class Event
{
    friend class EventDispatcher;

  public:
    Event()          = default;
    virtual ~Event() = default;

    virtual std::string ToString() const { return GetName(); }

  public:
    bool                  IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    bool                  IsHandled() const { return m_Handled; }
    virtual EventType     GetEventType() const     = 0;
    virtual EventCategory GetCategoryFlags() const = 0;
    virtual std::string   GetName() const          = 0;

  protected:
    bool m_Handled = false;
};

template <EventType Type, EventCategory... Categories> class EventBase : public Event
{
  public:
    static constexpr EventType GetStaticEventType() { return Type; }
    EventType                  GetEventType() const final { return Type; }
    EventCategory              GetCategoryFlags() const final { return (Categories | ...); }
    std::string                GetName() const final { return EventTypeToString(Type); }
};

class EventDispatcher
{
  public:
    explicit EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T, typename F> bool Dispatch(F&& handler)
    {
        static_assert(std::is_base_of_v<Event, T>, "T must be an Event type");
        if (m_Event.GetEventType() == T::GetStaticEventType()) {
            if constexpr (std::is_invocable_r_v<bool, F, T&>) {
                m_Event.m_Handled = handler(static_cast<T&>(m_Event));

                Logger::EngineTrace(std::format("Event dispatched {0} handled: {1}", m_Event.GetName(), m_Event.IsHandled()));
                return true;
            }
        }
        return false;
    }

  private:
    Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.ToString();
}
} // namespace Engine