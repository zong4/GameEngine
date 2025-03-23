#include "VertexBuffer.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLVertexBuffer.hpp"

std::unique_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(std::span<const float> vertices, BufferLayout layout, BufferUsage usage)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLVertexBuffer>(vertices, layout, usage);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}