#pragma once

// Core
#include "Core/Renderer/RendererContext.hpp"
#include "Core/Window/Window.hpp"

// Platform
#include <GLFW/glfw3.h>

namespace Engine
{
class GLFWWindow : public Window
{
  public:
    GLFWWindow(const WindowProps& props);
    virtual ~GLFWWindow() override;

    void        OnUpdate() override;
    inline void SetEventCallback(const std::function<void(Event&)>& callback) override
    {
        m_Data.EventCallback = callback;
    }

  public:
    inline unsigned int GetWidth() const override { return m_Data.Width; }
    inline unsigned int GetHeight() const override { return m_Data.Height; }
    inline void*        GetNativeWindow() const override { return m_Window; }
    inline bool         GetVSync() const override { return m_Data.VSync; }
    void                SetVSync(bool enabled) override;

  private:
    GLFWwindow*                      m_Window;
    std::unique_ptr<RendererContext> m_Context;

    struct WindowData {
        std::string  Title;
        unsigned int Width, Height;
        bool         VSync;

        std::function<void(Event&)> EventCallback;
    };
    WindowData m_Data;
};
} // namespace Engine