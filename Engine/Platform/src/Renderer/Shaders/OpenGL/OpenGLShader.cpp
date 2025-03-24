#include "OpenGLShader.hpp"

static GLenum ShaderTypeFromString(const std::string& type)
{
    if (type == "vertex")
    {
        return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel")
    {
        return GL_FRAGMENT_SHADER;
    }

    Engine::Logger::EngineAssert(false, "Unknown shader type");
    return 0;
}

Engine::OpenGLShader::OpenGLShader(const std::string& filepath)
    : Shader(filepath)
{
    std::string source = ReadFile(filepath);
    auto shaderSources = Preprocess(source);
    Compile(shaderSources);

    Logger::EngineTrace(
        std::format("OpenGL shader is constructed with ID: {0}", m_RendererID));
}

Engine::OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);

    Logger::EngineTrace(
        std::format("OpenGL shader is destructed with ID: {0}", m_RendererID));
}

void Engine::OpenGLShader::Bind() const { glUseProgram(m_RendererID); }

void Engine::OpenGLShader::Unbind() const { glUseProgram(0); }

void Engine::OpenGLShader::SetUniformMat4f(const std::string& name,
                                           const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
                       GL_FALSE, &matrix[0][0]);
}

void Engine::OpenGLShader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Engine::OpenGLShader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Engine::OpenGLShader::SetUniform2f(const std::string& name, float v0,
                                        float v1)
{
    glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1);
}

void Engine::OpenGLShader::SetUniform3f(const std::string& name, float v0,
                                        float v1, float v2)
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2);
}

void Engine::OpenGLShader::SetUniform4f(const std::string& name, float v0,
                                        float v1, float v2, float v3)
{
    glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2,
                v3);
}

std::string Engine::OpenGLShader::ReadFile(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    Logger::EngineAssert(file.is_open(),
                         std::format("Failed to open file: {0}", filepath));

    std::string fileContent;
    file.seekg(0, std::ios::end);
    fileContent.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&fileContent[0], fileContent.size());
    file.close();

    Logger::EngineInfo(std::format("File is read: {0}", filepath));
    return fileContent;
}

std::unordered_map<GLenum, std::string>
Engine::OpenGLShader::Preprocess(const std::string& source)
{
    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);

    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        Logger::EngineAssert(eol != std::string::npos, "Syntax error");

        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        Logger::EngineAssert(ShaderTypeFromString(type),
                             "Invalid shader type specified");

        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        Logger::EngineAssert(nextLinePos != std::string::npos, "Syntax error");
        pos = source.find(typeToken, nextLinePos);

        shaderSources[ShaderTypeFromString(type)] =
            source.substr(nextLinePos, pos - (nextLinePos == std::string::npos
                                                  ? source.size() - 1
                                                  : nextLinePos));
    }

    return shaderSources;
}

void Engine::OpenGLShader::Compile(
    const std::unordered_map<GLenum, std::string>& shaderSources)
{
    Logger::EngineAssert(shaderSources.size() <= 2,
                         "We only support 2 shaders for now"); // todo

    GLuint program = glCreateProgram();

    int shaderIDIndex = 0;
    std::array<GLuint, 2> shaderIDs;
    for (auto& kv : shaderSources)
    {
        GLenum type = kv.first;
        const std::string& source = kv.second;

        GLuint shader = glCreateShader(type);
        const char* sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            Logger::EngineError(std::format("{0}", infoLog.data()));
            break;
        }

        glAttachShader(program, shader);
        shaderIDs[shaderIDIndex++] = shader;
    }

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);
        for (auto id : shaderIDs)
        {
            glDeleteShader(id);
        }

        Logger::EngineError(std::format("{0}", infoLog.data()));
        return;
    }

    for (auto id : shaderIDs)
    {
        glDetachShader(program, id);
        glDeleteShader(id);
    }

    m_RendererID = program;
    Logger::EngineTrace(
        std::format("OpenGL shader is compiled with ID: {0}", m_RendererID));
}