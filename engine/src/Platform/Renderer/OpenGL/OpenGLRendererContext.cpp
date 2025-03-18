#include "OpenGLRendererContext.hpp"

#include <glad/glad.h>

void Engine::OpenGLRendererContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ENGINE_ASSERT(status, "Failed to initialize Glad!");

    ENGINE_INFO("OpenGL Info:");
    ENGINE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    ENGINE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    ENGINE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void Engine::OpenGLRendererContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}