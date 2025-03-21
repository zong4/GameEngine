#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
  public:
    ExampleLayer();
    virtual ~ExampleLayer();

    virtual void OnUpdate() override;
    virtual void BeginRender() override;
    virtual void OnImGuiRender() override;
    virtual void EndRender() override;

    virtual void OnEvent(Engine::Event& event) override;
    bool         OnKeyPressed(Engine::KeyPressedEvent& event);

  private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader>      m_Shader;

    std::shared_ptr<Engine::OrthographicCamera> m_Camera;
    float                                       m_CameraSpeed         = -0.1f;
    float                                       m_CameraRotationSpeed = -5.0f;
};