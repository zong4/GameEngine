#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

#include <glad/glad.h>

void Engine::OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    ENGINE_INFO("OpenGL renderer API is initialized");
}

void Engine::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

    ENGINE_INFO("OpenGL renderer API is drawing indexed");
}

void Engine::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ENGINE_INFO("OpenGL renderer API is clearing");
}

void Engine::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);

    ENGINE_INFO("OpenGL renderer API is setting viewport");
}

void Engine::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);

    ENGINE_INFO("OpenGL renderer API is setting clear color");
}
