#include "VertexBuffer.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLVertexBuffer.hpp"

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(uint32_t size)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(size);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(std::span<const float> vertices)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(std::span<const double> vertices)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}