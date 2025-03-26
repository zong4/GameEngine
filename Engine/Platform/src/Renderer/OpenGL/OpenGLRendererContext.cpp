#include "OpenGLRendererContext.hpp"

Engine::OpenGLRendererContext::OpenGLRendererContext(void* nativeWindow, bool vsync) : RendererContext(nativeWindow)
{
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_NativeWindow));
    if (glfwGetCurrentContext() != m_NativeWindow) {
        Logger::EngineAssert(false, "Failed to make OpenGL context current");
    }

    int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Logger::EngineAssert(gladStatus, "Failed to initialize Glad");

    Logger::EngineInfo("OpenGL Info:");
    Logger::EngineInfo(std::format("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
    Logger::EngineInfo(std::format("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
    Logger::EngineInfo(std::format("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    Logger::EngineInfo("OpenGL renderer context is constructed");
}

Engine::OpenGLRendererContext::~OpenGLRendererContext()
{
    glfwMakeContextCurrent(nullptr);

    Logger::EngineInfo("OpenGL renderer context is destructed");
}

void Engine::OpenGLRendererContext::SwapBuffers()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_NativeWindow));

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }
}