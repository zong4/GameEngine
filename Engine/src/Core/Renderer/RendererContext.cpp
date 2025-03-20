#include "RendererContext.hpp"

#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLRendererContext.hpp"

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* window)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLRendererContext>(static_cast<GLFWwindow*>(window));
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}