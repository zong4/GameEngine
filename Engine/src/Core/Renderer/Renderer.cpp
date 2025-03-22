#include "Renderer.hpp"

Engine::Renderer::SceneData Engine::Renderer::m_SceneData = {};

void Engine::Renderer::Init()
{
    RenderCommand::Init();
    ENGINE_INFO("Renderer initialized");
}

void Engine::Renderer::BeginScene(const OrthographicCamera& camera)
{
    m_SceneData.Camera = camera;
}

void Engine::Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    vertexArray->Bind();

    shader->Bind();
    shader->SetUniformMat4f("u_Transform", transform);
    shader->SetUniformMat4f("u_ViewProjection", m_SceneData.Camera.GetViewProjectionMatrix());

    RenderCommand::DrawIndexed(vertexArray);
}

void Engine::Renderer::EndScene()
{
}

void Engine::Renderer::Clear()
{
    RenderCommand::Clear();
}

void Engine::Renderer::Shutdown()
{
    ENGINE_INFO("Renderer shutdown");
}

void Engine::Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(0, 0, width, height);
}