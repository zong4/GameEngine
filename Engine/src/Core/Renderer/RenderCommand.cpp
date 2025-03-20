#include "RenderCommand.hpp"

std::unique_ptr<Engine::RendererAPI> Engine::RenderCommand::s_RendererAPI = Engine::RendererAPI::Create();