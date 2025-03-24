#pragma once

#include "../Camera/OrthographicCamera.hpp"
#include <platform.hpp>

namespace Engine {
class Renderer2D
{
public:
    static void Init();
    static void Shutdown();

    static void Clear(const glm::vec4& color);
    static void BeginScene(const OrthographicCamera& camera);
    static void Submit(const std::shared_ptr<Shader>& shader);
    static void EndScene();
    static void Flush();

    static void OnWindowResize(uint32_t width, uint32_t height);

    // Primitives
    static void DrawQuad(const glm::vec2& position,
                         float rotation = 0.0f,
                         const glm::vec2& size = {1.0f, 1.0f},
                         const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f},
                         const std::shared_ptr<Texture2D>& texture = nullptr,
                         const glm::vec2& tilingFactor = {1.0f, 1.0f});
    static void DrawQuad(const glm::vec3& position,
                         float rotation = 0.0f,
                         const glm::vec2& size = {1.0f, 1.0f},
                         const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f},
                         const std::shared_ptr<Texture2D>& texture = nullptr,
                         const glm::vec2& tilingFactor = {1.0f, 1.0f});

public:
    struct SceneData
    {
        OrthographicCamera Camera;

        SceneData() = default;
    };

protected:
    static std::unique_ptr<RendererAPI> s_RendererAPI;

private:
    static SceneData m_SceneData;
};
} // namespace Engine