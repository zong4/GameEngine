#include "IndexBuffer.hpp"

#include "Platform/Renderer/OpenGL/OpenGLIndexBuffer.hpp"
#include "Platform/Renderer/RendererAPI.hpp"

std::unique_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLIndexBuffer>(indices, count);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}