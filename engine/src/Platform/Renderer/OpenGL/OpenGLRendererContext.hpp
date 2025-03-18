#pragma once

// Platform
#include "Platform/Renderer/RendererContext.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class OpenGLRendererContext : public RendererContext
{
  public:
    OpenGLRendererContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}
    virtual ~OpenGLRendererContext() = default;

    virtual void Init() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
};
} // namespace Engine