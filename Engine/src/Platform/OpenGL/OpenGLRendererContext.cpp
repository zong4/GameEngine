#include "OpenGLRendererContext.hpp"

// Platform
#include <glad/glad.h>

void Engine::OpenGLRendererContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ENGINE_ASSERT(status, "Failed to initialize Glad!");

    ENGINE_INFO("OpenGL renderer context is initialized");
    ENGINE_INFO("OpenGL Info:");
    ENGINE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    ENGINE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    ENGINE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Engine::OpenGLRendererContext::~OpenGLRendererContext()
{
    ENGINE_INFO("OpenGL renderer context is destroyed");
}

void Engine::OpenGLRendererContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}