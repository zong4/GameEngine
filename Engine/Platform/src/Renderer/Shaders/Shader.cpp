#include "Shader.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLShader.hpp"
#elif __linux__
#include "OpenGL/OpenGLShader.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLShader.hpp"
#endif

std::shared_ptr<Engine::Shader> Engine::Shader::Create(const std::string& filepath)
{
#ifdef _WIN32
    return std::make_shared<OpenGLShader>(filepath);
#elif __linux__
    return std::make_shared<OpenGLShader>(filepath);
#elif __APPLE__
    return std::make_shared<OpenGLShader>(filepath);
#endif
}

std::string Engine::Shader::ReadFile(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    Logger::EngineAssert(file.is_open(), std::format("Failed to open file: {0}", filepath));

    std::string fileContent;
    file.seekg(0, std::ios::end);
    fileContent.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&fileContent[0], fileContent.size());
    file.close();

    Logger::EngineInfo(std::format("File is read: {0}", filepath));
    return fileContent;
}