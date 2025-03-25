#pragma once

#include "../RendererAPI.hpp"
#include <glad/glad.h>

namespace Engine {
class OpenGLRendererAPI final : public RendererAPI
{
public:
    explicit OpenGLRendererAPI();
    virtual ~OpenGLRendererAPI();
    OpenGLRendererAPI(const OpenGLRendererAPI&) = delete;
    OpenGLRendererAPI& operator=(const OpenGLRendererAPI&) = delete;

    virtual void Clear() override;
    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void DrawIndexed(const VertexArray& vertexArray) override;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
} // namespace Engine