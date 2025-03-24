#include "VertexBuffer.hpp"

#include "OpenGL/OpenGLVertexBuffer.hpp"
#include "Platform/Renderer/RendererAPI.hpp"

std::unique_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}