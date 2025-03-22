#include "Shader.hpp"

#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

std::unique_ptr<Engine::Shader> Engine::Shader::Create(const std::string& filepath)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLShader>(filepath);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}