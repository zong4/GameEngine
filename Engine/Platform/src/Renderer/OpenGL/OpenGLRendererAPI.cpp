#include "OpenGLRendererAPI.hpp"

void Engine::OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    Logger::EngineInfo("OpenGL renderer API is initialized");
}

void Engine::OpenGLRendererAPI::Shutdown()
{
    Logger::EngineInfo("OpenGL renderer API is shutdown");
}

void Engine::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::OpenGLRendererAPI::DrawIndexed(
    const std::unique_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(),
                   GL_UNSIGNED_INT, nullptr);
}

void Engine::OpenGLRendererAPI::DrawIndexed(
    const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(),
                   GL_UNSIGNED_INT, nullptr);
}

void Engine::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y,
                                            uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);

    Logger::EngineInfo("OpenGL renderer API is setting viewport");
}

void Engine::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}
