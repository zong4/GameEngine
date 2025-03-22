#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
enum class EventType {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
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

#define EVENT_CLASS_TYPE(type)                                                                                                                                 \
    inline static EventType GetStaticType()                                                                                                                    \
    {                                                                                                                                                          \
        return EventType::type;                                                                                                                                \
    }                                                                                                                                                          \
    inline virtual EventType GetEventType() const override                                                                                                     \
    {                                                                                                                                                          \
        return GetStaticType();                                                                                                                                \
    }                                                                                                                                                          \
    inline virtual const char* GetName() const override                                                                                                        \
    {                                                                                                                                                          \
        return #type;                                                                                                                                          \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                                                         \
    inline virtual EventCategory GetCategoryFlags() const override                                                                                             \
    {                                                                                                                                                          \
        return category;                                                                                                                                       \
    }

class Event
{
    friend class EventDispatcher;

  public:
    Event()          = default;
    virtual ~Event() = default;

    virtual inline std::string ToString() const { return GetName(); }

  public:
    virtual EventType     GetEventType() const     = 0;
    virtual const char*   GetName() const          = 0;
    virtual EventCategory GetCategoryFlags() const = 0;
    inline bool           IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    inline bool           IsHandled() const { return m_Handled; }

  protected:
    bool m_Handled = false;
};

class EventDispatcher
{
  public:
    explicit EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T, typename F> bool Dispatch(F&& handler)
    {
        static_assert(std::is_base_of_v<Event, T>, "T must be an Event type");
        if (m_Event.GetEventType() == T::GetStaticType()) {
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