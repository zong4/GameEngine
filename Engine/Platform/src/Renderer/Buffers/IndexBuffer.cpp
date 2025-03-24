#include "IndexBuffer.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLIndexBuffer.hpp"

std::unique_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}