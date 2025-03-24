#pragma once

#include "../../Renderer/RendererContext.hpp"
#include "../Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class GLFWWindow final : public Window
{
  public:
    explicit GLFWWindow(const WindowProps& props);
    virtual ~GLFWWindow() override;

    void OnUpdate() override;
    void SetEventCallback(const std::function<void(Event&)>& callback) override;

  public:
    virtual void* GetNativeWindow() const override { return m_Window; }
    virtual void  SetVSync(bool enabled) override;

  private:
    GLFWwindow*                      m_Window;
    std::unique_ptr<RendererContext> m_Context;
};
} // namespace Engine