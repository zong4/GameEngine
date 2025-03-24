#pragma once

#include "../Camera/OrthographicCamera.hpp"
#include <platform.hpp>

namespace Engine {
class Renderer3D
{
public:
    static void Init();
    static void Shutdown();

    static void Clear(const glm::vec4& color);
    static void BeginScene(const OrthographicCamera& camera);
    static void Submit(const std::unique_ptr<Shader>& shader,
                       const VertexArray& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));
    static void Submit(const std::unique_ptr<Shader>& shader,
                       const std::shared_ptr<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));
    static void EndScene();

    static void OnWindowResize(uint32_t width, uint32_t height);

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