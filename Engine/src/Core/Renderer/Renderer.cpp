#include "Renderer.hpp"

void Engine::Renderer::BeginScene()
{
}

void Engine::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Engine::Renderer::EndScene()
{
}

void Engine::Renderer::Shutdown()
{
}
