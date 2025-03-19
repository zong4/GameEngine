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

enum EventCategory {
    None                     = 0,
    EventCategoryApplication = ENGINE_BIT(0),
    EventCategoryInput       = ENGINE_BIT(1),
    EventCategoryKeyboard    = ENGINE_BIT(2),
    EventCategoryMouse       = ENGINE_BIT(3),
    EventCategoryMouseButton = ENGINE_BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    inline static EventType GetStaticType()                                                                            \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    inline virtual EventType GetEventType() const override                                                             \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    inline virtual const char* GetName() const override                                                                \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    virtual int GetCategoryFlags() const override                                                                      \
    {                                                                                                                  \
        return category;                                                                                               \
    }

class Event
{
    friend class EventDispatcher;

  public:
    Event()          = default;
    virtual ~Event() = default;

    virtual inline std::string ToString() const { return GetName(); }

  public:
    virtual EventType   GetEventType() const     = 0;
    virtual const char* GetName() const          = 0;
    virtual int         GetCategoryFlags() const = 0;
    inline bool         IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    inline bool         IsHandled() const { return m_Handled; }

  protected:
    bool m_Handled = false;
};

class EventDispatcher
{
    template <typename T> using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T> bool Dispatch(EventFn<T> func)
    {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.m_Handled = func(*(T*)&m_Event);
            return true;
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