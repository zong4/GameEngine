#pragma once

#include "../Camera/OrthographicCamera.hpp"
#include <platform.hpp>

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
    static void DrawQuad(const glm::vec2& position, float rotation = 0.0f,
                         const glm::vec2& size = {1.0f, 1.0f},
                         const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f},
                         const std::shared_ptr<Texture2D>& texture = nullptr,
                         const glm::vec2& tilingFactor = {1.0f, 1.0f});
    static void DrawQuad(const glm::vec3& position, float rotation = 0.0f,
                         const glm::vec2& size = {1.0f, 1.0f},
                         const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f},
                         const std::shared_ptr<Texture2D>& texture = nullptr,
                         const glm::vec2& tilingFactor = {1.0f, 1.0f});
};
} // namespace Engine