#include "RendererAPI.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

#ifdef PLATFORM_WINDOWS
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif PLATFORM_LINUX
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif PLATFORM_MACOSX
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#endif

std::unique_ptr<Engine::RendererAPI> Engine::RendererAPI::Create()
{
    switch (s_API) {
    case API::OpenGL:
        return std::make_unique<Engine::OpenGLRendererAPI>();
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}