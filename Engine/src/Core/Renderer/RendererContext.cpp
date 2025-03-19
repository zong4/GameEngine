#include "RendererContext.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLRendererContext.hpp"

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* window)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLRendererContext>(static_cast<GLFWwindow*>(window));
    }
}