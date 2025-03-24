#include "Renderer2D.hpp"

std::unique_ptr<Engine::RendererAPI> Engine::Renderer2D::s_RendererAPI = nullptr;

namespace Engine {
struct Renderer2DStorage
{
    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<Shader> TextureShader;
    std::shared_ptr<Texture2D> WhiteTexture;
};

static std::unique_ptr<Renderer2DStorage> s_Data = std::make_unique<Renderer2DStorage>();
} // namespace Engine

void Engine::Renderer2D::Init()
{
    s_RendererAPI = RendererAPI::Create();

    s_Data->QuadVertexArray = VertexArray::Create();

    float vertices[4 * 5] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    };
    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"},
    };
    s_Data->QuadVertexArray->AddVertexBuffer(VertexBuffer::Create(vertices, layout));

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    s_Data->QuadVertexArray->SetIndexBuffer(IndexBuffer::Create(indices));

    s_Data->TextureShader = Shader::Create(std::string(PROJECT_DIR) + "/Engine/assets/shaders/Texture.glsl");

    constexpr uint32_t width = 2, height = 2;
    s_Data->WhiteTexture = Texture2D::Create(width, height);
    std::uint32_t whiteTextureData[width * height] = {0xffffffff, 0x00ffffff, 0xff00ffff, 0x0000ffff};
    s_Data->WhiteTexture->SetData(whiteTextureData);

    Logger::EngineInfo("Renderer2D is initialized");
}

void Engine::Renderer2D::Shutdown()
{
    s_Data.reset();
    Logger::EngineInfo("Renderer2D is shutdown");
}

void Engine::Renderer2D::Clear(const glm::vec4& color)
{
    s_RendererAPI->SetClearColor(color);
    s_RendererAPI->Clear();
}

void Engine::Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetUniformMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Engine::Renderer2D::Submit(const std::shared_ptr<Shader>& shader)
{
    shader->Bind();
}

void Engine::Renderer2D::EndScene() {}

void Engine::Renderer2D::Flush() {}

void Engine::Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
{
    s_RendererAPI->SetViewport(0, 0, width, height);
}

void Engine::Renderer2D::DrawQuad(const glm::vec2& position,
                                  float rotation,
                                  const glm::vec2& size,
                                  const glm::vec4& color,
                                  const std::shared_ptr<Texture2D>& texture,
                                  const glm::vec2& tilingFactor)
{
    DrawQuad({position.x, position.y, 0.0f}, rotation, size, color, texture, tilingFactor);
}

void Engine::Renderer2D::DrawQuad(const glm::vec3& position,
                                  float rotation,
                                  const glm::vec2& size,
                                  const glm::vec4& color,
                                  const std::shared_ptr<Texture2D>& texture,
                                  const glm::vec2& tilingFactor)
{
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetUniformMat4f("u_Transform",
                                           glm::translate(glm::mat4(1.0f), position) *
                                               glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) *
                                               glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}));

    s_Data->TextureShader->SetUniform4f("u_Color", color);

    s_Data->TextureShader->SetUniform1i("u_Texture", 0);
    s_Data->TextureShader->SetUniform2f("u_TilingFactor", tilingFactor);
    if (texture == nullptr) {
        s_Data->WhiteTexture->Bind();
    } else {
        texture->Bind();
    }

    s_Data->QuadVertexArray->Bind();
    s_RendererAPI->DrawIndexed(s_Data->QuadVertexArray);
}