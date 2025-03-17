#include "GLFWWindow.hpp"

#include "../../Core/Events/ApplicationEvent.hpp"
#include "../../Core/Events/KeyEvent.hpp"
#include "../../Core/Events/MouseEvent.hpp"

static void GLFWErrorCallback(int error, const char *description)
{
    ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
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

    glfwSetErrorCallback(GLFWErrorCallback);

    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        ENGINE_ERROR("Could not create window");
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
                              {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event); });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
                               {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        data.EventCallback(event); });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS:
        {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        default:
            break;
        } });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
                               {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS:
        {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
        }
        default:
            break;
        } });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
                          {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event); });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
                             {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event); });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, int focused)
                               {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        if (focused)
        {
            WindowFocusEvent event;
            data.EventCallback(event);
        }
        else
        {
            WindowLostFocusEvent event;
            data.EventCallback(event);
        } });

    glfwSetWindowPosCallback(m_Window, [](GLFWwindow *window, int xPos, int yPos)
                             {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        WindowMovedEvent event(xPos, yPos);
        data.EventCallback(event); });

    ENGINE_INFO("Window created");
}

void Engine::GLFWWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
