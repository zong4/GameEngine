#include "OpenGLShader.hpp"

Engine::OpenGLShader::OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    std::string vertexSource   = ReadFile(std::string(PROJECT_DIR) + "/" + vertexFilepath);
    std::string fragmentSource = ReadFile(std::string(PROJECT_DIR) + "/" + fragmentFilepath);

    Compile(std::unordered_map<GLenum, std::string>{{GL_VERTEX_SHADER, vertexSource}, {GL_FRAGMENT_SHADER, fragmentSource}});
}

Engine::OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);

    ENGINE_INFO("OpenGL shader is deleted with ID: {0}", m_RendererID);
}

void Engine::OpenGLShader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Engine::OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void Engine::OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Engine::OpenGLShader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Engine::OpenGLShader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Engine::OpenGLShader::SetUniform2f(const std::string& name, float v0, float v1)
{
    glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1);
}

void Engine::OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2);
}

void Engine::OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2, v3);
}

std::string Engine::OpenGLShader::ReadFile(const std::string& filepath)
{
    std::ifstream file(std::string(PROJECT_DIR) + "/" + filepath, std::ios::in | std::ios::binary);
    ENGINE_ASSERT(file, "Failed to open file: {0}", filepath);

    std::string fileContent;
    file.seekg(0, std::ios::end);
    fileContent.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&fileContent[0], fileContent.size());
    file.close();

    ENGINE_INFO("File is read: {0}", filepath);
    return fileContent;
}

void Engine::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
    m_RendererID = glCreateProgram();
    ENGINE_ASSERT(m_RendererID, "Failed to create shader program!");

    std::unordered_map<GLenum, GLuint> shaderIDs;
    for (const auto& [type, source] : shaderSources) {
        GLuint      shader     = glCreateShader(type);
        const char* sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            ENGINE_ERROR("Shader compilation failed: {0}", infoLog.data());
            ENGINE_ASSERT(false, "Shader compilation failed!");
            return;
        }

        glAttachShader(m_RendererID, shader);
        shaderIDs[type] = shader;
    }

    glLinkProgram(m_RendererID);

    GLint isLinked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(m_RendererID);

        for (const auto& [type, shader] : shaderIDs) {
            glDeleteShader(shader);
        }

        ENGINE_ERROR("Shader linking failed: {0}", infoLog.data());
        ENGINE_ASSERT(false, "Shader linking failed!");
        return;
    }

    for (const auto& [type, shader] : shaderIDs) {
        glDetachShader(m_RendererID, shader);
        glDeleteShader(shader);
    }

    ENGINE_INFO("OpenGL shader is created with ID: {0}", m_RendererID);
}