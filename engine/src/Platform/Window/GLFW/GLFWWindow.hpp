#pragma once

// Platform
#include "Platform/Window/Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class GLFWWindow : public Window
{
  public:
    GLFWWindow(const WindowProps& props) { Init(props); }
    ~GLFWWindow() override { Shutdown(); }

    inline unsigned int GetWidth() const override { return m_Data.Width; }
    inline unsigned int GetHeight() const override { return m_Data.Height; }
    inline void*        GetNativeWindow() const override { return m_Window; }
    inline bool         IsVSync() const override { return m_Data.VSync; }
    void                SetVSync(bool enabled) override;
    inline void         SetEventCallback(const std::function<void(Event&)>& callback) override
    {
        m_Data.EventCallback = callback;
    }

    void OnUpdate() override;

  private:
    void Init(const WindowProps& props);
    void Shutdown();

  private:
    GLFWwindow* m_Window;

    struct WindowData {
        std::string  Title;
        unsigned int Width, Height;
        bool         VSync;

        std::function<void(Event&)> EventCallback;
    };
    WindowData m_Data;
};
} // namespace Engine