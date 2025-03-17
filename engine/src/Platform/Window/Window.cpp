#include "Window.hpp"

#include "GLFW/GLFWWindow.hpp"

Engine::Window *Engine::Window::Create(const WindowProps &props)
{
#ifdef PLATFORM_WINDOWS
    return new GLFWWindow(props);
#elif PLATFORM_LINUX
    return new GLFWWindow(props);
#elif PLATFORM_MACOSX
    return new GLFWWindow(props);
#endif
}