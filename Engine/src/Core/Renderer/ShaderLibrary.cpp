#include "ShaderLibrary.hpp"

void Engine::ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
    const std::string& name = shader->GetName();
    Add(name, shader);
}

void Engine::ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    ENGINE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
    m_Shaders[name] = shader;
}

std::shared_ptr<Engine::Shader> Engine::ShaderLibrary::Load(const std::string& filepath)
{
    std::shared_ptr<Shader> shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

std::shared_ptr<Engine::Shader> Engine::ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    std::shared_ptr<Shader> shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Engine::Shader> Engine::ShaderLibrary::Get(const std::string& name)
{
    ENGINE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
    return m_Shaders[name];
}

bool Engine::ShaderLibrary::Exists(const std::string& name)
{
    return m_Shaders.find(name) != m_Shaders.end();
}