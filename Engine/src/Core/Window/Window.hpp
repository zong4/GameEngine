#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/Event.hpp"

namespace Engine
{
struct WindowProps {
    std::string  Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Game Engine", unsigned int width = 1280, unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
  public:
    Window()                         = default;
    virtual ~Window()                = default;
    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    virtual void OnUpdate()                                                    = 0;
    virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;

    static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());

  public:
    virtual unsigned int GetWidth() const        = 0;
    virtual unsigned int GetHeight() const       = 0;
    virtual void*        GetNativeWindow() const = 0;
    virtual bool         GetVSync() const        = 0;
    virtual void         SetVSync(bool enabled)  = 0;
};
} // namespace Engine