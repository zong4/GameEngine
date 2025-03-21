#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer() : Layer("ExampleLayer")
{
    m_Camera = std::make_shared<Engine::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

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

    std::string vertexSrc   = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        uniform mat4 u_Transform;
        uniform mat4 u_ViewProjection;

        out vec3 v_Position;
        out vec2 v_TexCoord;

        void main()
        {
            v_Position = a_Position;
            v_TexCoord = a_TexCoord;
            
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";
    std::string fragmentSrc = R"(
        #version 330 core

        uniform vec4 u_Color;

        in vec3 v_Position;
        in vec2 v_TexCoord;

        layout(location = 0) out vec4 color;

        void main()
        {
            color = u_Color;
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
        m_Camera->SetPosition({m_Camera->GetPosition().x, m_Camera->GetPosition().y + m_CameraMoveSpeed * timestep, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_S)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x, m_Camera->GetPosition().y - m_CameraMoveSpeed * timestep, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_A)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x - m_CameraMoveSpeed * timestep, m_Camera->GetPosition().y, m_Camera->GetPosition().z});
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_D)) {
        m_Camera->SetPosition({m_Camera->GetPosition().x + m_CameraMoveSpeed * timestep, m_Camera->GetPosition().y, m_Camera->GetPosition().z});
    }

    if (Engine::Input::IsKeyPressed(ENGINE_KEY_Q)) {
        m_Camera->SetRotation(m_Camera->GetRotation() + m_CameraRotationSpeed * timestep);
    }
    if (Engine::Input::IsKeyPressed(ENGINE_KEY_E)) {
        m_Camera->SetRotation(m_Camera->GetRotation() - m_CameraRotationSpeed * timestep);
    }

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

    Engine::Renderer::BeginScene(m_Camera);
    {
        m_Shader->SetUniform4f("u_Color", m_Color);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(i * 0.11f, j * 0.11f, 0.0f)) * scale;
                Engine::Renderer::Submit(m_Shader, m_VertexArray, transform);
            }
        }
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
}