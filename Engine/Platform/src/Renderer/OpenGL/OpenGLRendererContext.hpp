#pragma once

#include "../RendererContext.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine {
class OpenGLRendererContext final : public RendererContext
{
public:
    explicit OpenGLRendererContext(GLFWwindow* windowHandle);
    virtual ~OpenGLRendererContext();
    OpenGLRendererContext(const OpenGLRendererContext&) = delete;
    OpenGLRendererContext& operator=(const OpenGLRendererContext&) = delete;

    virtual void SwapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};
} // namespace Engine