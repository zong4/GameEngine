#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer() : Layer("ExampleLayer")
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
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t                             indices[6]  = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<Engine::IndexBuffer> indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_ShaderLibrary = Engine::Shader::Create("Editor/assets/shaders/Texture.glsl");

    m_Texture   = Engine::Texture2D::Create("Editor/assets/textures/head.png");
    m_TextureBG = Engine::Texture2D::Create("Editor/assets/textures/02.jpg");

    EDITOR_INFO("ExampleLayer is initialized");
}

ExampleLayer::~ExampleLayer()
{
    EDITOR_INFO("ExampleLayer is destroyed");
}

void ExampleLayer::OnUpdate(Engine::Timestep timestep)
{
    m_CameraController->OnUpdate(timestep);

    if (Engine::Input::IsKeyPressed(ENGINE_KEY_I)) {
        m_ObjectPosition.y += m_ObjectMoveSpeed * timestep;
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_K)) {
        m_ObjectPosition.y -= m_ObjectMoveSpeed * timestep;
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_J)) {
        m_ObjectPosition.x -= m_ObjectMoveSpeed * timestep;
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_L)) {
        m_ObjectPosition.x += m_ObjectMoveSpeed * timestep;
    }

    if (Engine::Input::IsKeyPressed(ENGINE_KEY_U)) {
        m_ObjectRotation += m_ObjectRotationSpeed * timestep;
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_O)) {
        m_ObjectRotation -= m_ObjectRotationSpeed * timestep;
    }

    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_CameraController->GetCamera());
    {
        m_ShaderLibrary->Bind();
        m_Texture->Bind();
        m_ShaderLibrary->SetUniform1i("u_Texture", 0);
        m_ShaderLibrary->SetUniform4f("u_Color", m_Color);

        glm::mat4 scale     = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ObjectPosition) * scale;
        Engine::Renderer::Submit(m_ShaderLibrary, m_VertexArray, transform);

        m_TextureBG->Bind();
        m_ShaderLibrary->SetUniform1i("u_Texture", 0);
        m_ShaderLibrary->SetUniform4f("u_Color", m_Color);
        Engine::Renderer::Submit(m_ShaderLibrary, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
    }
    Engine::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void ExampleLayer::OnEvent(Engine::Event& event)
{
    m_CameraController->OnEvent(event);
}