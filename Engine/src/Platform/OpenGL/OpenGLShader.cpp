#include "OpenGLShader.hpp"

// Platform
#include <glad/glad.h>

Engine::OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    // Create an empty vertex shader handle
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Get the vertex source code
    const char* vertexSrcCStr = vertexSrc.c_str();

    // Set the vertex source code
    glShaderSource(vertexShader, 1, &vertexSrcCStr, nullptr);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Check if the vertex shader compiled successfully
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        ENGINE_ERROR("Vertex shader compilation failed: {0}", infoLog);

        // Delete the vertex shader
        glDeleteShader(vertexShader);
        return;
    }

    // Create an empty fragment shader handle
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Get the fragment source code
    const char* fragmentSrcCStr = fragmentSrc.c_str();

    // Set the fragment source code
    glShaderSource(fragmentShader, 1, &fragmentSrcCStr, nullptr);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    // Check if the fragment shader compiled successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        ENGINE_ERROR("Fragment shader compilation failed: {0}", infoLog);

        // Delete the vertex and fragment shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    // Create an empty shader program handle
    m_RendererID = glCreateProgram();

    // Attach the vertex and fragment shaders to the shader program
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);

    // Link the shader program
    glLinkProgram(m_RendererID);

    // Check if the shader program linked successfully
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
        ENGINE_ERROR("Shader program linking failed: {0}", infoLog);

        // Delete the program
        glDeleteProgram(m_RendererID);

        // Delete the vertex and fragment shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    // Always detach shaders after a successful link
    glDetachShader(m_RendererID, vertexShader);
    glDetachShader(m_RendererID, fragmentShader);

    ENGINE_INFO("OpenGL shader is created with ID: {0}", m_RendererID);
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