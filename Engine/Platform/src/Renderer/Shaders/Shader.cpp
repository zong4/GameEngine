#include "Shader.hpp"

#include "../RendererAPI.hpp"
#include "OpenGL/OpenGLShader.hpp"

std::shared_ptr<Engine::Shader> Engine::Shader::Create(const std::string& filepath)
{
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filepath);
        default:
            Logger::EngineAssert(false, "Unknown RendererAPI");
            return nullptr;
    }
}