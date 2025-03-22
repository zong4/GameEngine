#include "EditorLayer2D.hpp"

EditorLayer2D::EditorLayer2D() : Layer("EditorLayer2D")
{
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

    Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        Engine::Renderer2D::DrawQuad({m_ObjectPosition.x, m_ObjectPosition.y, 0.1f}, {1.0f, 1.0f}, m_Color);
        Engine::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
    }
    Engine::Renderer2D::EndScene();
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