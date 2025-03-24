#include "ShaderLibrary.hpp"

void Engine::ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    Logger::EngineAssert(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists in the library");
    m_Shaders[name] = shader;
}

std::shared_ptr<Engine::Shader> Engine::ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    std::shared_ptr<Shader> shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Engine::Shader> Engine::ShaderLibrary::Get(const std::string& name)
{
    Logger::EngineAssert(m_Shaders.find(name) != m_Shaders.end(), "Shader not found in the library");
    return m_Shaders[name];
}

bool Engine::ShaderLibrary::Exists(const std::string& name)
{
    return m_Shaders.find(name) != m_Shaders.end();
}