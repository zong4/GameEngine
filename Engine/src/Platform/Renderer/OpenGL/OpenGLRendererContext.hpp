#pragma once

#include "Platform/Renderer/RendererContext.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class OpenGLRendererContext : public RendererContext
{
  public:
    OpenGLRendererContext(GLFWwindow* windowHandle);
    virtual ~OpenGLRendererContext();

    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
};
} // namespace Engine