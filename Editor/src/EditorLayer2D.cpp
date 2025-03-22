#include "EditorLayer2D.hpp"

EditorLayer2D::EditorLayer2D() : Layer("EditorLayer2D")
{
    m_VertexArray = Engine::VertexArray::Create();

    float vertices[4 * 5] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));

    Engine::BufferLayout layout = {
        {Engine::ShaderDataType::Float3, "a_Position"},
        {Engine::ShaderDataType::Float2, "a_TexCoord"},
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(std::move(vertexBuffer));

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    m_VertexArray->SetIndexBuffer(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    m_ShaderLibrary = Engine::Shader::Create("Editor/assets/shaders/Texture.glsl");
    m_Texture       = Engine::Texture2D::Create("Editor/assets/textures/head.png");
    m_TextureBG     = Engine::Texture2D::Create("Editor/assets/textures/02.jpg");

    EDITOR_INFO("EditorLayer2D is constructed");
}

EditorLayer2D::~EditorLayer2D() noexcept
{
    EDITOR_INFO("EditorLayer2D is destructed");
}

void EditorLayer2D::OnUpdate(const Engine::Timestep& timestep)
{
    m_CameraController.OnUpdate(timestep);

    // todo: remove
    {
        if (Engine::Input::IsKeyPressed(ENGINE_KEY_I))
            m_ObjectPosition.y += m_ObjectMoveSpeed * timestep;

        if (Engine::Input::IsKeyPressed(ENGINE_KEY_K))
            m_ObjectPosition.y -= m_ObjectMoveSpeed * timestep;

        if (Engine::Input::IsKeyPressed(ENGINE_KEY_J))
            m_ObjectPosition.x -= m_ObjectMoveSpeed * timestep;

        if (Engine::Input::IsKeyPressed(ENGINE_KEY_L))
            m_ObjectPosition.x += m_ObjectMoveSpeed * timestep;

        if (Engine::Input::IsKeyPressed(ENGINE_KEY_U))
            m_ObjectRotation += m_ObjectRotationSpeed * timestep;

        if (Engine::Input::IsKeyPressed(ENGINE_KEY_O))
            m_ObjectRotation -= m_ObjectRotationSpeed * timestep;
    }

    Engine::RenderCommand::SetClearColor(m_ColorBG);
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_CameraController.GetCamera());
    {
        m_ShaderLibrary->Bind();
        m_ShaderLibrary->SetUniform4f("u_Color", m_Color);

        m_Texture->Bind();
        m_ShaderLibrary->SetUniform1i("u_Texture", 0);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ObjectPosition);
        Engine::Renderer::Submit(m_ShaderLibrary, m_VertexArray, transform);

        m_TextureBG->Bind();
        m_ShaderLibrary->SetUniform1i("u_Texture", 0);
        Engine::Renderer::Submit(m_ShaderLibrary, m_VertexArray, glm::mat4(1.0f));
    }
    Engine::Renderer::EndScene();
}

void EditorLayer2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void EditorLayer2D::OnEvent(Engine::Event& event)
{
    m_CameraController.OnEvent(event);
}