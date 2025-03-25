#include "RendererContext.hpp"

#include "OpenGL/OpenGLRendererContext.hpp"
#include "RendererAPI.hpp"
#include "Vulkan/VulkanRendererContext.hpp"

std::weak_ptr<Engine::RendererContext> Engine::RendererContext::s_Instance;

std::shared_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* windowHandle)
{
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::OpenGL:
            s_Instance = std::make_shared<OpenGLRendererContext>(windowHandle);
            return Get();
        case RendererAPI::API::Vulkan:
            s_Instance = std::make_shared<VulkanRendererContext>(windowHandle);
            return Get();
        default:
            Logger::EngineAssert(false, "Unknown RendererAPI");
            return Get();
    }
}