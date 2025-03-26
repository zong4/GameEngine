#include "BGFXWindow.hpp"

static void GLFWErrorCallback(int error, const char* description)
{
    Engine::Logger::EngineAssert(false, std::format("GLFW Error ({0}): {1}", error, description));
}

Engine::BGFXWindow::BGFXWindow(const WindowProps& props) : Window(props)
{
    if (!glfwInit()) {
        Logger::EngineAssert(false, "Could not initialize GLFW");
        return;
    }
    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        Logger::EngineAssert(false, "Could not create glfw window for BGFX");
        return;
    }

    m_Context = RendererContext::Create(m_Window, m_Data.VSync);

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            if (focused) {
                WindowFocusEvent event;
                data.EventCallback(event);
            } else {
                WindowLostFocusEvent event;
                data.EventCallback(event);
            }
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowMovedEvent event(xPos, yPos);
            data.EventCallback(event);
        });
    }

    Logger::EngineInfo(
        std::format("GLFW window {0} ({1}, {2}) is constructed", m_Data.Title, m_Data.Width, m_Data.Height));
}

Engine::BGFXWindow::~BGFXWindow()
{
    m_Context.reset();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    Logger::EngineInfo("GLFW window is destructed");
}

void Engine::BGFXWindow::OnUpdate()
{
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void Engine::BGFXWindow::SetEventCallback(const std::function<void(Event&)>& callback)
{
    m_Data.EventCallback = std::move(callback);
}

void Engine::BGFXWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.VSync = enabled;
}