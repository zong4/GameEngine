#pragma once

#include "Buffers/VertexArray.hpp"

namespace Engine {
class RendererAPI
{
public:
    virtual ~RendererAPI() = default;
    RendererAPI(const RendererAPI&) = delete;
    RendererAPI& operator=(const RendererAPI&) = delete;

public:
    virtual void Clear() = 0;
    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void DrawIndexed(const VertexArray& vertexArray) = 0;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

    static std::unique_ptr<RendererAPI> Create();

protected:
    RendererAPI() = default;
};
} // namespace Engine