#pragma once

#include "VertexArray.hpp"

namespace Engine
{
class RendererAPI
{
  public:
    enum class API {
        OpenGL = 1,
    };

  public:
    virtual void Init()                                                       = 0;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
    virtual void Clear()                                                      = 0;

    static std::unique_ptr<RendererAPI> Create();

  public:
    inline static API GetAPI() { return s_API; }
    virtual void      SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void      SetClearColor(const glm::vec4& color)                                = 0;

  private:
    static API s_API;
};
} // namespace Engine