#include "IndexBuffer.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"

std::unique_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}