#pragma once

// Core
#include "Core/Events/Event.hpp"
#include "Core/Renderer/RendererContext.hpp"

namespace Engine
{
enum class RendererAPI { None = 0, OpenGL = 1, /*Vulkan = 2, DirectX = 3, Metal = 4*/ };

class Renderer
{
  public:
    inline static RendererAPI GetAPI() { return s_RendererAPI; }

  private:
    static RendererAPI s_RendererAPI;
};
} // namespace Engine