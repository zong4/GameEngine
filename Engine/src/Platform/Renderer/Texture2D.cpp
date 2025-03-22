#include "Texture2D.hpp"

#include "Platform/Renderer/OpenGL/OpenGLTexture2D.hpp"
#include "Platform/Renderer/RendererAPI.hpp"

std::unique_ptr<Engine::Texture2D> Engine::Texture2D::Create(const std::string& path)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLTexture2D>(path);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}