#include "Texture2D.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLTexture2D.hpp"

std::shared_ptr<Engine::Texture2D> Engine::Texture2D::Create(uint32_t width, uint32_t height)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(width, height);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}

std::shared_ptr<Engine::Texture2D> Engine::Texture2D::Create(const std::string& path)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(path);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI");
        return nullptr;
    }
}
