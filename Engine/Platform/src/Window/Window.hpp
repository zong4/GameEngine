#pragma once

#include <core.hpp>

namespace Engine
{
struct WindowProps {
    std::string Title;
    int         Width;
    int         Height;
    bool        VSync;

    WindowProps(const std::string& title, int width, int height, bool vsync = true) : Title(title), Width(width), Height(height), VSync(vsync) {}
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

  public:
    bool          IsVSync() const { return m_Data.VSync; }
    std::size_t   GetWidth() const { return m_Data.Width; }
    std::size_t   GetHeight() const { return m_Data.Height; }
    virtual void* GetNativeWindow() const = 0;
    virtual void  SetVSync(bool enabled)  = 0;

  protected:
    Window(const WindowProps& props) : m_Data(props) {}

  protected:
    struct WindowData {
        std::string Title;
        int         Width = 0, Height = 0;
        bool        VSync = false;

        std::function<void(Event&)> EventCallback;

        WindowData(const WindowProps& props) : Title(props.Title), Width(props.Width), Height(props.Height), VSync(props.VSync) {}
    };
    WindowData m_Data;
};
} // namespace Engine