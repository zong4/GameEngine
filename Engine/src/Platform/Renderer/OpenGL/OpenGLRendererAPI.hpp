#pragma once

#include "Platform/Renderer/RendererAPI.hpp"

namespace Engine
{
class OpenGLRendererAPI : public RendererAPI
{
  public:
    virtual void Init() override;
    virtual void DrawIndexed(const std::unique_ptr<VertexArray>& vertexArray) override;
    virtual void Clear() override;

  public:
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void SetClearColor(const glm::vec4& color) override;
};
} // namespace Engine