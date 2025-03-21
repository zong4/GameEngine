#include "Texture2D.hpp"

#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLTexture2D.hpp"

std::shared_ptr<Engine::Texture2D> Engine::Texture2D::Create(const std::string& path)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(path);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}