#include "Input.hpp"

#include "Platform/Input/GLFW/GLFWInput.hpp"

std::unique_ptr<Engine::Input> Engine::Input::s_Instance = nullptr;

void Engine::Input::Init(void* window)
{
#ifdef _WIN32
    s_Instance = std::make_unique<GLFWInput>();
#elif PLATFORM_LINUX
    s_Instance = std::make_unique<GLFWInput>();
#elif __APPLE__
    s_Instance = std::make_unique<GLFWInput>(window);
#endif
    Logger::EngineInfo("Input system is initialized");
}

void Engine::Input::Shutdown()
{
    s_Instance.reset();
    Logger::EngineInfo("Input system is shutdown");
}