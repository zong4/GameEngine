#pragma once

#include "Core/Renderer/RenderCommand.hpp"

namespace Engine
{
class Renderer
{
  public:
    inline static void Init() { RenderCommand::Init(); }
    static void        BeginScene();
    static void        Submit(const std::shared_ptr<VertexArray>& vertexArray);
    static void        EndScene();
    inline static void Clear() { RenderCommand::Clear(); }
    static void        Shutdown();
};
} // namespace Engine