#include "BGFXRendererAPI.hpp"

Engine::BGFXRendererAPI::BGFXRendererAPI()
{
    Logger::EngineInfo("BGFX renderer API is constructed");
}

Engine::BGFXRendererAPI::~BGFXRendererAPI()
{
    Logger::EngineInfo("BGFX renderer API is destructed");
}

void Engine::BGFXRendererAPI::Clear()
{
    bgfx::touch(0);
}

void Engine::BGFXRendererAPI::SetClearColor(const glm::vec4& color)
{
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, color.r, color.g, color.b, color.a);
}

void Engine::BGFXRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    bgfx::setViewRect(0, x, y, width, height);

    Logger::EngineInfo("BGFX renderer API is setting viewport");
}

void Engine::BGFXRendererAPI::DrawIndexed(const VertexArray& vertexArray) {}

void Engine::BGFXRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {}
