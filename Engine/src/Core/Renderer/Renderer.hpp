#pragma once

#include "Core/Renderer/OrthographicCamera.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Shader.hpp"

namespace Engine
{
class Renderer
{
  public:
    static void Init();
    static void BeginScene(const OrthographicCamera& camera);
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    static void EndScene();
    static void Clear();
    static void Shutdown();

  public:
    struct SceneData {
        OrthographicCamera Camera;

        SceneData() = default;
    };

  private:
    static SceneData m_SceneData;
};
} // namespace Engine