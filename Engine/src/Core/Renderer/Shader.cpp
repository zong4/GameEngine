#include "Shader.hpp"

#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

std::shared_ptr<Engine::Shader> Engine::Shader::Create(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLShader>(vertexFilepath, fragmentFilepath);
    default:
        ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}