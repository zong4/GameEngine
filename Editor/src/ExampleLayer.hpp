#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
  public:
    ExampleLayer();
    virtual ~ExampleLayer();

    virtual void OnUpdate(Engine::Timestep timestep) override;
    virtual void OnImGuiRender() override;

    virtual void OnEvent(Engine::Event& event) override;

  private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader>      m_Shader;
    glm::vec4                            m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    std::shared_ptr<Engine::Texture2D>   m_Texture;

    std::shared_ptr<Engine::OrthographicCamera> m_Camera;
    float                                       m_CameraMoveSpeed     = -5.0f;
    float                                       m_CameraRotationSpeed = -180.0f;

    glm::vec3 m_ObjectPosition      = glm::vec3(0.0f, 0.0f, 0.0f);
    float     m_ObjectRotation      = 0.0f;
    float     m_ObjectMoveSpeed     = 5.0f;
    float     m_ObjectRotationSpeed = 180.f;
};