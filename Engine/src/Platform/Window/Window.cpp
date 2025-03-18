#include "Window.hpp"

// Platform
#include "Platform/Window/GLFW/GLFWWindow.hpp"

std::unique_ptr<Engine::Window> Engine::Window::Create(const WindowProps& props)
{
#ifdef PLATFORM_WINDOWS
    return std::make_unique<GLFWWindow>(props);
#elif PLATFORM_LINUX
    return std::make_unique<GLFWWindow>(props);
#elif PLATFORM_MACOSX
    return std::make_unique<GLFWWindow>(props);
#endif
}