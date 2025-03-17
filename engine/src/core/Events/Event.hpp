#pragma once

#include "../../EnginePCH.hpp"

#define BIT(x) (1 << x)

namespace Engine
{
    /// @brief Event types
    enum class EventType
    {
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
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    /// @brief One-hot enum for event categories
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

/// @brief Macros for event classes
#define EVENT_CLASS_TYPE(type)                                                         \
    inline static EventType GetStaticType() { return EventType::type; }                \
    inline virtual EventType GetEventType() const override { return GetStaticType(); } \
    inline virtual const char *GetName() const override { return #type; }

/// @brief Macros for event categories
#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    /// @brief Base class for all events
    class Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType GetEventType() const = 0;
        virtual const char *GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual inline std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        inline bool IsHandled() const { return m_Handled; }

    protected:
        bool m_Handled = false;
    };

    /// @brief Event dispatcher
    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        EventDispatcher(Event &event)
            : m_Event(event) {}

        template <typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled = func(*(T *)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };
} // namespace Engine