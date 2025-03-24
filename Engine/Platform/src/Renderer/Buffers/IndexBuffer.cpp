#include "IndexBuffer.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLIndexBuffer.hpp"

std::shared_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t size)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(size);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}

std::shared_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(std::span<uint32_t> indices)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indices);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}