#pragma once

#include "EnginePCH.hpp"

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

    virtual std::string_view ToString() const { return GetName(); }

  public:
    virtual EventType        GetEventType() const     = 0;
    virtual EventCategory    GetCategoryFlags() const = 0;
    virtual std::string_view GetName() const          = 0;
    bool                     IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    bool                     IsHandled() const { return m_Handled; }

  protected:
    bool m_Handled = false;
};

template <EventType Type, EventCategory... Categories> class EventBase : public Event
{
  public:
    static constexpr EventType GetStaticEventType() { return Type; }
    EventType                  GetEventType() const final { return Type; }
    EventCategory              GetCategoryFlags() const final { return (Categories | ...); }
    std::string_view           GetName() const final { return m_Name; }

  private:
    static constexpr std::string_view m_Name = []() constexpr {
        if constexpr (std::is_same_v<decltype(Type), EventType>) {
            return "EventName";
        }
        return "UnknownEvent";
    }();
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