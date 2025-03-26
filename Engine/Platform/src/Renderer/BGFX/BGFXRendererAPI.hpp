#pragma once

#include "../RendererAPI.hpp"
#include <bgfx/bgfx.h>

namespace Engine {
class BGFXRendererAPI final : public RendererAPI
{
public:
    explicit BGFXRendererAPI();
    virtual ~BGFXRendererAPI();
    BGFXRendererAPI(const BGFXRendererAPI&) = delete;
    BGFXRendererAPI& operator=(const BGFXRendererAPI&) = delete;

    virtual void Clear() override;
    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void DrawIndexed(const VertexArray& vertexArray) override;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
} // namespace Engine