#include "RendererContext.hpp"

#include "Platform/Renderer/OpenGL/OpenGLRendererContext.hpp"
#include "Platform/Renderer/RendererAPI.hpp"

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* window)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLRendererContext>(static_cast<GLFWwindow*>(window));
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}