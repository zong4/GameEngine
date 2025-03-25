#include "RendererAPI.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLRendererAPI.hpp"
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif __linux__
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif __APPLE__
#include "Vulkan/VulkanRendererAPI.hpp"
Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#endif

std::unique_ptr<Engine::RendererAPI> Engine::RendererAPI::Create()
{

    #ifdef _WIN32
    return std::make_unique<Engine::OpenGLRendererAPI>();
#elif __linux__
    Engine::RendererAPI::API Engine::RendererAPI::s_API = Engine::RendererAPI::API::OpenGL;
#elif __APPLE__
#include "Vulkan/VulkanRendererAPI.hpp"
    return std::make_unique<Engine::VulkanRendererAPI>();
#endif

            Logger::EngineAssert(false, "Unknown RendererAPI");
            return nullptr;
    
}