#pragma once

#include "Platform/Renderer/RendererAPI.hpp"

namespace Engine
{
class RenderCommand
{
  public:
    static void Init() { s_RendererAPI->Init(); }
    static void DrawIndexed(const std::unique_ptr<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
    static void Clear() { s_RendererAPI->Clear(); }

  public:
    static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }

  private:
    static std::unique_ptr<RendererAPI> s_RendererAPI;
};
} // namespace Engine