#pragma once

#include "Core/Events/Event.hpp"

namespace Engine
{
struct WindowProps {
    std::string Title;
    std::size_t Width;
    std::size_t Height;
    bool        VSync;

    WindowProps(const std::string& title, std::size_t width, std::size_t height, bool vsync = true) : Title(title), Width(width), Height(height), VSync(vsync)
    {
    }
};

class Window
{
  public:
    virtual ~Window()                = default;
    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    virtual void OnUpdate()                                                    = 0;
    virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;

    static std::unique_ptr<Window> Create(const WindowProps& props);

  protected:
    Window(const WindowProps& props) : m_Data(props) {}

  public:
    bool          IsVSync() const { return m_Data.VSync; }
    std::size_t   GetWidth() const { return m_Data.Width; }
    std::size_t   GetHeight() const { return m_Data.Height; }
    virtual void* GetNativeWindow() const = 0;
    virtual void  SetVSync(bool enabled)  = 0;

  protected:
    struct WindowData {
        std::string Title;
        std::size_t Width = 0, Height = 0;
        bool        VSync = false;

        std::function<void(Event&)> EventCallback;

        WindowData(const WindowProps& props) : Title(props.Title), Width(props.Width), Height(props.Height), VSync(props.VSync) {}
    };
    WindowData m_Data;
};
} // namespace Engine