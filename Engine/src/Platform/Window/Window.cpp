#include "Window.hpp"

#include "Platform/Window/GLFW/GLFWWindow.hpp"

std::unique_ptr<Engine::Window> Engine::Window::Create(const WindowProps& props)
{
#ifdef _WIN32
    return std::make_unique<GLFWWindow>(props);
#elif __linux__
    return std::make_unique<GLFWWindow>(props);
#elif __APPLE__
    return std::make_unique<GLFWWindow>(props);
#endif
    return nullptr;
}