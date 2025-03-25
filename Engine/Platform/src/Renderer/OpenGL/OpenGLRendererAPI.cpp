#include "OpenGLRendererAPI.hpp"

Engine::OpenGLRendererAPI::OpenGLRendererAPI()
{
    // Enable blending
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLint error = glGetError();
        if (error != GL_NO_ERROR) {
            Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
        }
    }

    // Enable depth testing
    {
        glEnable(GL_DEPTH_TEST);

        GLint error = glGetError();
        if (error != GL_NO_ERROR) {
            Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
        }
    }

    Logger::EngineInfo("OpenGL renderer API is constructed");
}

Engine::OpenGLRendererAPI::~OpenGLRendererAPI()
{
    Logger::EngineInfo("OpenGL renderer API is destructed");
}

void Engine::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }
}

void Engine::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }
}

void Engine::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }

    Logger::EngineInfo("OpenGL renderer API is setting viewport");
}

void Engine::OpenGLRendererAPI::DrawIndexed(const VertexArray& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }
}

void Engine::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::EngineAssert(false, std::format("OpenGL error: {0}", error));
    }
}
