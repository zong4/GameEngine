#include "VertexArray.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLVertexArray.hpp"

std::shared_ptr<Engine::VertexArray> Engine::VertexArray::Create()
{
    switch (RendererAPI::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        default:
            Logger::EngineAssert(false, "Unknown RendererAPI");
            return nullptr;
    }
}