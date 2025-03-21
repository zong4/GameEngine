#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer() : Layer("ExampleLayer")
{
    m_Camera = std::make_shared<Engine::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

    m_VertexArray = Engine::VertexArray::Create();

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
    };
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));

    Engine::BufferLayout layout = {
        {Engine::ShaderDataType::Float3, "a_Position"},
        {Engine::ShaderDataType::Float4, "a_Color"},
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t                             indices[3]  = {0, 1, 2};
    std::shared_ptr<Engine::IndexBuffer> indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexSrc   = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
        }
    )";
    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
    )";
    m_Shader                = Engine::Shader::Create(vertexSrc, fragmentSrc);

    EDITOR_INFO("ExampleLayer is initialized");
}

ExampleLayer::~ExampleLayer()
{
    EDITOR_INFO("ExampleLayer is destroyed");
}

void ExampleLayer::OnUpdate(Engine::Timestep timestep)
{
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_W)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x, m_Camera->GetPosition().y + m_CameraSpeed * timestep, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_S)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x, m_Camera->GetPosition().y - m_CameraSpeed * timestep, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_A)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x - m_CameraSpeed * timestep, m_Camera->GetPosition().y, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_D)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x + m_CameraSpeed * timestep, m_Camera->GetPosition().y, m_Camera->GetPosition().z});
    }

    if (Engine::Input::IsKeyPressed(ENGINE_KEY_Q)) {
        m_Camera->SetRotation(m_Camera->GetRotation() + m_CameraRotationSpeed * timestep);
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_E)) {
        m_Camera->SetRotation(m_Camera->GetRotation() - m_CameraRotationSpeed * timestep);
    }

    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_Camera);
    {
        Engine::Renderer::Submit(m_Shader, m_VertexArray);
    }
    Engine::Renderer::EndScene();
}

void ExampleLayer::BeginRender()
{
}

void ExampleLayer::OnImGuiRender()
{
}

void ExampleLayer::EndRender()
{
}

void ExampleLayer::OnEvent(Engine::Event& event)
{
}