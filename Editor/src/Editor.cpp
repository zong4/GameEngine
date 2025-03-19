#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
  public:
    ExampleLayer() : Layer("ExampleLayer") {}

    virtual void OnAttach() override { EDITOR_INFO("ExampleLayer::OnAttach"); }
    virtual void OnUpdate() override
    {
        if (Engine::Input::IsKeyPressed(ENGINE_KEY_TAB))
            EDITOR_INFO("Tab key is pressed");
    }
    virtual void BeginRender() override {}
    virtual void OnImGuiRender() override {}
    virtual void EndRender() override {}
    virtual void OnEvent(Engine::Event& event) override
    {
        if (event.GetEventType() == Engine::EventType::KeyPressed) {
            EDITOR_INFO("Key pressed: {0} ({1})", (Engine::KeyPressedEvent&)event.GetKeyCode(),
                        (char)(Engine::KeyPressedEvent&)event.GetKeyCode());
        }
    }
    virtual void OnDetach() override { EDITOR_INFO("ExampleLayer::OnDetach"); }
};

class Editor : public Engine::Application
{
  public:
    Editor()
    {
        EDITOR_INFO("Editor constructor");
        PushLayer(new ExampleLayer());
    }
    ~Editor() { EDITOR_INFO("Editor destructor"); }
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Editor>();
}