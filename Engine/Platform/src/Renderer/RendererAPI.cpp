#include "RendererAPI.hpp"

#include "OpenGL/OpenGLRendererAPI.hpp"
#include "Vulkan/VulkanRendererAPI.hpp"

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
        case API::Vulkan:
            return std::make_unique<Engine::VulkanRendererAPI>();
        default:
            Logger::EngineAssert(false, "Unknown RendererAPI");
            return nullptr;
    }
}