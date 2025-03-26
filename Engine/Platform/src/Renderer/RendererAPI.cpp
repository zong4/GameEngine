#include "RendererAPI.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLRendererAPI.hpp"
#elif __linux__
#include "OpenGL/OpenGLRendererAPI.hpp"
#elif __APPLE__
#include "BGFX/BGFXRendererAPI.hpp"
#endif

std::unique_ptr<Engine::RendererAPI> Engine::RendererAPI::Create()
{
#ifdef _WIN32
    return std::make_unique<Engine::OpenGLRendererAPI>();
#elif __linux__
    return std::make_unique<Engine::OpenGLRendererAPI>();
#elif __APPLE__
    return std::make_unique<Engine::BGFXRendererAPI>();
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}