#pragma once

#include "Platform/Renderer/RendererContext.hpp"
#include "Platform/Window/Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class GLFWWindow : public Window
{
  public:
    GLFWWindow(const WindowProps& props);
    virtual ~GLFWWindow() override;

    void OnUpdate() override;
    void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; }

  public:
    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }
    void*        GetNativeWindow() const override { return m_Window; }
    bool         GetVSync() const override { return m_Data.VSync; }
    void         SetVSync(bool enabled) override;

  private:
    GLFWwindow*                      m_Window = nullptr;
    std::unique_ptr<RendererContext> m_Context;

    struct WindowData {
        std::string  Title;
        unsigned int Width = 0, Height = 0;
        bool         VSync = false;

        std::function<void(Event&)> EventCallback;
    };
    WindowData m_Data;
};
} // namespace Engine