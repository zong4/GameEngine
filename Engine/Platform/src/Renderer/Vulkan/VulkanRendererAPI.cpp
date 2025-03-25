#include "VulkanRendererAPI.hpp"

Engine::VulkanRendererAPI::VulkanRendererAPI()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    Logger::EngineInfo("OpenGL renderer API is constructed");
}

Engine::VulkanRendererAPI::~VulkanRendererAPI()
{
    Logger::EngineInfo("OpenGL renderer API is destructed");
}

void Engine::VulkanRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::VulkanRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Engine::VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);

    Logger::EngineInfo("OpenGL renderer API is setting viewport");
}

void Engine::VulkanRendererAPI::DrawIndexed(const VertexArray& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
}

void Engine::VulkanRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
}
