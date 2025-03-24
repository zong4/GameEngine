#pragma once

#include "Functions/Camera/OrthographicCamera.hpp"
#include "Platform/Renderer/Texture2D.hpp"

namespace Engine
{
class Renderer2D
{
  public:
    static void Init();
    static void Shutdown();
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();

    // Primitives
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f);

  private:
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture,
                         float tilingFactor);
};
} // namespace Engine