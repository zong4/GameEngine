#include "Window.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLWindow.hpp"
#elif __linux__
#include "OpenGL/OpenGLWindow.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLWindow.hpp"
#include "Vulkan/VulkanWindow.hpp"
#endif

std::unique_ptr<Engine::Window> Engine::Window::Create(const WindowProps& props)
{
#ifdef _WIN32
    return std::make_unique<OpenGLWindow>(props);
#elif __linux__
    return std::make_unique<OpenGLWindow>(props);
#elif __APPLE__
    return std::make_unique<OpenGLWindow>(props);
#endif
    return nullptr;
}