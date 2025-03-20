#pragma once

namespace Engine
{
enum class RendererAPI { OpenGL = 1, /*Vulkan = 2, DirectX = 3, Metal = 4*/ };

class Renderer
{
  public:
    inline static RendererAPI GetAPI() { return s_RendererAPI; }

  private:
    static RendererAPI s_RendererAPI;
};
} // namespace Engine