#pragma once

#include "Functions/Camera/OrthographicCamera.hpp"
#include <platform.hpp>

namespace Engine
{
class Renderer
{
  public:
    static void Init();
    static void BeginScene(const OrthographicCamera& camera);
    static void Submit(const std::unique_ptr<Shader>& shader, const std::unique_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    static void EndScene();
    static void Clear();
    static void Shutdown();

  public:
    static void OnWindowResize(uint32_t width, uint32_t height);

  public:
    struct SceneData {
        OrthographicCamera Camera;

        SceneData() = default;
    };

  private:
    static SceneData m_SceneData;
};
} // namespace Engine