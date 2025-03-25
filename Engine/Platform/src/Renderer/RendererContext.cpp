#include "RendererContext.hpp"

#include "OpenGL/OpenGLRendererContext.hpp"
#include "RendererAPI.hpp"
#include "Vulkan/VulkanRendererContext.hpp"

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* windowHandle)
{
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_unique<OpenGLRendererContext>(windowHandle);
        case RendererAPI::API::Vulkan:
            return std::make_unique<VulkanRendererContext>(windowHandle);
        default:
            Logger::EngineAssert(false, "Unknown RendererAPI");
            return nullptr;
    }
}