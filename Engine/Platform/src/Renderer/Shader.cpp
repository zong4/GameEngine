#include "Shader.hpp"

#include "OpenGL/OpenGLShader.hpp"
#include "RendererAPI.hpp"

std::unique_ptr<Engine::Shader> Engine::Shader::Create(const std::string& filepath)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_unique<OpenGLShader>(filepath);
    default:
        Logger::EngineAssert(false, "Unknown RendererAPI!");
        return nullptr;
    }
}