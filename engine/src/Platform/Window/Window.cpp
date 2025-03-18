#include "Window.hpp"

// Platform
#include "GLFW/GLFWWindow.hpp"

Engine::Window* Engine::Window::Create(const WindowProps& props)
{
#ifdef PLATFORM_WINDOWS
    return std::make_unique<GLFWWindow>(props);
#elif PLATFORM_LINUX
    return std::make_unique<GLFWWindow>(props);
#elif PLATFORM_MACOSX
    return new GLFWWindow(props);
#endif
}