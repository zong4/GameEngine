#include "Shader.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLShader.hpp"

std::unique_ptr<Engine::Shader> Engine::Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}