#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/Event.hpp"

namespace Engine
{
struct WindowProps {
    std::string Title;
    std::size_t Width;
    std::size_t Height;

    WindowProps(const std::string& title, std::size_t width, std::size_t height) : Title(title), Width(width), Height(height) {}
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

    static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps("Game Engine", 1280, 720));

  public:
    virtual std::size_t GetWidth() const        = 0;
    virtual std::size_t GetHeight() const       = 0;
    virtual void*       GetNativeWindow() const = 0;
    virtual bool        GetVSync() const        = 0;
    virtual void        SetVSync(bool enabled)  = 0;
};
} // namespace Engine