#include "VertexBuffer.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}