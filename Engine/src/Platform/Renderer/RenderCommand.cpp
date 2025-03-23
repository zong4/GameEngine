#include "RenderCommand.hpp"

std::unique_ptr<Engine::RendererAPI> Engine::RenderCommand::s_RendererAPI = Engine::RendererAPI::Create();

void Engine::RenderCommand::Shutdown()
{
    s_RendererAPI->Shutdown();
    s_RendererAPI.reset();
}