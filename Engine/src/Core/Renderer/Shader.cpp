#include "Shader.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/OpenGL/OpenGLShader.hpp"

std::unique_ptr<Engine::Shader> Engine::Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
    }
}