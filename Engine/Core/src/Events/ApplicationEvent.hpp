#pragma once

#include "Event.hpp"

namespace Engine
{
class AppTickEvent
    : public EventBase<EventType::AppTick, EventCategory::Application>
{
public:
    AppTickEvent() = default;
};

class AppUpdateEvent
    : public EventBase<EventType::AppUpdate, EventCategory::Application>
{
public:
    AppUpdateEvent() = default;
};

class AppRenderEvent
    : public EventBase<EventType::AppRender, EventCategory::Application>
{
public:
    AppRenderEvent() = default;
};
} // namespace Engine