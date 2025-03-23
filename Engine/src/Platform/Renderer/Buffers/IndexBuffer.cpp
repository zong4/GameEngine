#include "IndexBuffer.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLIndexBuffer.hpp"

std::unique_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(std::span<const uint32_t> indices, BufferUsage usage)
{
    if (indices.empty()) {
        Logger::EngineWarn("Index buffer is empty");
        return nullptr;
    }

    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLIndexBuffer>(indices, usage);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}