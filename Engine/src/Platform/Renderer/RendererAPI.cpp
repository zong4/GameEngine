#include "RendererAPI.hpp"

#include "Platform/Renderer/OpenGL/OpenGLRendererAPI.hpp"

#ifdef _WIN32
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif __linux__
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif __APPLE__
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#endif

std::unique_ptr<Engine::RendererAPI> Engine::RendererAPI::Create()
{
    switch (s_API) {
    case API::OpenGL:
        return std::make_unique<Engine::OpenGLRendererAPI>();
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}