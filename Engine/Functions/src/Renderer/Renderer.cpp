#include "Renderer.hpp"

#include "Renderer2D.hpp"

Engine::Renderer::SceneData Engine::Renderer::m_SceneData = {};

void Engine::Renderer::Init()
{
    RenderCommand::Init();
    Renderer2D::Init();
    Logger::EngineInfo("Renderer is initialized");
}

void Engine::Renderer::BeginScene(const OrthographicCamera& camera)
{
    m_SceneData.Camera = camera;
}

void Engine::Renderer::Submit(const std::unique_ptr<Shader>& shader,
                              const std::unique_ptr<VertexArray>& vertexArray,
                              const glm::mat4& transform)
{
    vertexArray->Bind();

    shader->Bind();
    shader->SetUniformMat4f("u_Transform", transform);
    shader->SetUniformMat4f("u_ViewProjection",
                            m_SceneData.Camera.GetViewProjectionMatrix());

    RenderCommand::DrawIndexed(vertexArray);
}

void Engine::Renderer::EndScene() {}

void Engine::Renderer::Clear() { RenderCommand::Clear(); }

void Engine::Renderer::Shutdown()
{
    Renderer2D::Shutdown();
    RenderCommand::Shutdown();
    Logger::EngineInfo("Renderer is shutdown");
}

void Engine::Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(0, 0, width, height);
}