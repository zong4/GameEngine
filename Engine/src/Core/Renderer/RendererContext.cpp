#include "RendererContext.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLRendererContext.hpp"

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* window)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLRendererContext>(static_cast<GLFWwindow*>(window));
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}