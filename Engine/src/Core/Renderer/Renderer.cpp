#include "Renderer.hpp"

Engine::Renderer::SceneData Engine::Renderer::m_SceneData = {};

void Engine::Renderer::Init()
{
    RenderCommand::Init();
    ENGINE_INFO("Renderer initialized");
}

void Engine::Renderer::BeginScene(const std::shared_ptr<OrthographicCamera>& camera)
{
    m_SceneData.Camera = camera;
}

void Engine::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
{
    vertexArray->Bind();
    shader->Bind();
    shader->SetUniformMat4f("u_ViewProjection", m_SceneData.Camera->GetViewProjectionMatrix());
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
