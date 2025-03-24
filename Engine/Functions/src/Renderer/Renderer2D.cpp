#include "Renderer2D.hpp"

#include <platform.hpp>

namespace Engine
{
struct Renderer2DStorage {
    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<Shader>      TextureShader;
    std::shared_ptr<Texture2D>   WhiteTexture;
};

static std::unique_ptr<Renderer2DStorage> s_Data = std::make_unique<Renderer2DStorage>();
} // namespace Engine

void Engine::Renderer2D::Init()
{
    s_Data->QuadVertexArray = VertexArray::Create();

    float vertices[4 * 5] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };
    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices);

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"},
    };
    vertexBuffer->SetLayout(layout);
    s_Data->QuadVertexArray->AddVertexBuffer(std::move(vertexBuffer));

    uint32_t                     indices[6]  = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices);
    s_Data->QuadVertexArray->SetIndexBuffer(std::move(indexBuffer));

    s_Data->TextureShader = Shader::Create(std::string(PROJECT_DIR) + "/Engine/assets/shaders/Texture.glsl");

    s_Data->WhiteTexture      = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    Logger::EngineInfo("Renderer2D is initialized");
}

void Engine::Renderer2D::Shutdown()
{
    s_Data.reset();
    Logger::EngineInfo("Renderer2D is shutdown");
}

void Engine::Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetUniformMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Engine::Renderer2D::EndScene()
{
}

void Engine::Renderer2D::Flush()
{
}

void Engine::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
}

void Engine::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad(position, size, color, s_Data->WhiteTexture, 1.0f);
}

void Engine::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor)
{
    DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor);
}

void Engine::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor)
{
    DrawQuad(position, size, glm::vec4(1.0f), texture, tilingFactor);
}

void Engine::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture,
                                  float tilingFactor)
{
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetUniformMat4f("u_Transform", glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}));

    s_Data->TextureShader->SetUniform4f("u_Color", color);

    s_Data->TextureShader->SetUniform1i("u_Texture", 0);
    s_Data->TextureShader->SetUniform1f("u_TilingFactor", tilingFactor);
    texture->Bind();

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}