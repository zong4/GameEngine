#include "VertexBuffer.hpp"

#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

std::unique_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}