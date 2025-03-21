#include "VertexArray.hpp"

#include "Platform/Renderer/OpenGL/OpenGLVertexArray.hpp"
#include "Platform/Renderer/RendererAPI.hpp"

std::unique_ptr<Engine::VertexArray> Engine::VertexArray::Create()
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLVertexArray>();
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}