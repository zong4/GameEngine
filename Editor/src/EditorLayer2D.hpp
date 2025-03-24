#include <functions.hpp>

class EditorLayer2D : public Engine::Layer
{
public:
    EditorLayer2D();
    virtual ~EditorLayer2D() override;

    virtual void OnUpdate(const Engine::Timestep& timestep) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Engine::Event& event) override;

private:
    Engine::OrthographicCameraController m_CameraController =
        Engine::OrthographicCameraController(1280.0f / 720.0f, true);

    Engine::ShaderLibrary m_ShaderLibrary;
    std::shared_ptr<Engine::Texture2D> m_Texture;
    std::shared_ptr<Engine::Texture2D> m_TextureBG;
    glm::vec4 m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 m_ColorBG = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

    glm::vec3 m_ObjectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float m_ObjectRotation = 0.0f;
    float m_ObjectMoveSpeed = 5.0f;
    float m_ObjectRotationSpeed = 180.f;
};