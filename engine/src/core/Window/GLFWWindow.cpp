#include "GLFWWindow.hpp"

Engine::GLFWWindow::GLFWWindow(const WindowProps &props)
{
    Init(props);
}

Engine::GLFWWindow::~GLFWWindow()
{
    Shutdown();
}

void Engine::GLFWWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Engine::GLFWWindow::SetVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    m_Data.VSync = enabled;
}

bool Engine::GLFWWindow::IsVSync() const
{
    return m_Data.VSync;
}

void Engine::GLFWWindow::Init(const WindowProps &props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    ENGINE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!glfwInit())
    {
        ENGINE_ERROR("Could not initialize GLFW");
        return;
    }

    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        ENGINE_ERROR("Could not create window");
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

void Engine::GLFWWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}