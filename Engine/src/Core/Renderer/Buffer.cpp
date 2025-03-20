#include "Buffer.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLBuffer.hpp"

std::unique_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}

std::unique_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}