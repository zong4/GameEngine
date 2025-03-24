#include "OpenGLRendererContext.hpp"

#include <glad/glad.h>

Engine::OpenGLRendererContext::OpenGLRendererContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Logger::EngineAssert(status, "Failed to initialize Glad");

    Logger::EngineInfo("OpenGL Info:");
    Logger::EngineInfo(std::format("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
    Logger::EngineInfo(std::format("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
    Logger::EngineInfo(std::format("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    Logger::EngineInfo("OpenGL renderer context is initialized");
}

Engine::OpenGLRendererContext::~OpenGLRendererContext()
{
    Logger::EngineInfo("OpenGL renderer context is destroyed");
}

void Engine::OpenGLRendererContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}