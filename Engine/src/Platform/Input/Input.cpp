#include "Input.hpp"

#include "Platform/Input/GLFW/GLFWInput.hpp"

std::unique_ptr<Engine::Input> Engine::Input::s_Instance = nullptr;

void Engine::Input::Init()
{
#ifdef PLATFORM_WINDOWS
    s_Instance = std::make_unique<GLFWInput>();
#elif PLATFORM_LINUX
    s_Instance = std::make_unique<GLFWInput>();
#elif __APPLE__
    s_Instance = std::make_unique<GLFWInput>();
#endif
    Logger::EngineAssert(s_Instance, "Input system is not initialized");
}

void Engine::Input::Shutdown()
{
    Logger::EngineInfo("Input system is shutting down");
}