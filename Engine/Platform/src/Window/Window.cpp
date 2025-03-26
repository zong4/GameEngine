#include "Window.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLWindow.hpp"
#elif __linux__
#include "Vulkan/VulkanWindow.hpp"
#elif __APPLE__
#include "BGFX/BGFXWindow.hpp"
#endif

std::unique_ptr<Engine::Window> Engine::Window::Create(const WindowProps& props)
{
#ifdef _WIN32
    return std::make_unique<OpenGLWindow>(props);
#elif __linux__
    return std::make_unique<VulkanWindow>(props);
#elif __APPLE__
    return std::make_unique<BGFXWindow>(props);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}