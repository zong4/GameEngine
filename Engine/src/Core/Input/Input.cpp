#include "Input.hpp"

// Platform
#include "Platform/GLFW/GLFWInput.hpp"

std::unique_ptr<Engine::Input> Engine::Input::s_Instance = nullptr;

void Engine::Input::Init()
{
#ifdef PLATFORM_WINDOWS
    s_Instance = std::make_unique<GLFWInput>();
#elif PLATFORM_LINUX
    s_Instance = std::make_unique<GLFWInput>();
#elif PLATFORM_MACOSX
    s_Instance = std::make_unique<GLFWInput>();
#endif
    ENGINE_ASSERT(s_Instance, "Input system is not initialized");
}