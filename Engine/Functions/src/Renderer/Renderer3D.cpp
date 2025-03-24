#include "Renderer3D.hpp"

std::unique_ptr<Engine::RendererAPI> Engine::Renderer3D::s_RendererAPI = nullptr;

Engine::Renderer3D::SceneData Engine::Renderer3D::m_SceneData = {};

void Engine::Renderer3D::Init()
{
    s_RendererAPI = RendererAPI::Create();

    Logger::EngineInfo("Renderer3D is initialized");
}

void Engine::Renderer3D::Shutdown()
{
    s_RendererAPI.reset();

    Logger::EngineInfo("Renderer3D is shutdown");
}

void Engine::Renderer3D::Clear(const glm::vec4& color)
{
    s_RendererAPI->SetClearColor(color);
    s_RendererAPI->Clear();
}

void Engine::Renderer3D::BeginScene(const OrthographicCamera& camera)
{
    m_SceneData.Camera = camera;
}

void Engine::Renderer3D::Submit(const std::unique_ptr<Shader>& shader,
                                const VertexArray& vertexArray,
                                const glm::mat4& transform)
{
    vertexArray.Bind();

    shader->Bind();
    shader->SetUniformMat4f("u_Transform", transform);
    shader->SetUniformMat4f("u_ViewProjection", m_SceneData.Camera.GetViewProjectionMatrix());

    s_RendererAPI->DrawIndexed(vertexArray);
}

void Engine::Renderer3D::Submit(const std::unique_ptr<Shader>& shader,
                                const std::shared_ptr<VertexArray>& vertexArray,
                                const glm::mat4& transform)
{
    vertexArray->Bind();

    shader->Bind();
    shader->SetUniformMat4f("u_Transform", transform);
    shader->SetUniformMat4f("u_ViewProjection", m_SceneData.Camera.GetViewProjectionMatrix());

    s_RendererAPI->DrawIndexed(vertexArray);
}

void Engine::Renderer3D::EndScene() {}

void Engine::Renderer3D::OnWindowResize(uint32_t width, uint32_t height)
{
    s_RendererAPI->SetViewport(0, 0, width, height);
}