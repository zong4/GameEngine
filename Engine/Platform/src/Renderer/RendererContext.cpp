#include "RendererContext.hpp"

#include "RendererAPI.hpp"
#ifdef _WIN32
#include "OpenGL/OpenGLRendererContext.hpp"
#elif __linux__
#include "OpenGL/OpenGLWindow.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLWindow.hpp"
#include "Vulkan/VulkanRendererContext.hpp"
#endif

std::weak_ptr<Engine::RendererContext> Engine::RendererContext::s_Instance;

std::shared_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* windowHandle)
{
#ifdef _WIN32
    return std::make_shared<OpenGLRendererContext>(windowHandle);
#elif __linux__
#include "OpenGL/OpenGLWindow.hpp"
#elif __APPLE__
    s_Instance = std::make_shared<VulkanRendererContext>(windowHandle);
    return Get();
#endif

            Logger::EngineAssert(false, "Unknown RendererAPI");
            return Get();
    
}