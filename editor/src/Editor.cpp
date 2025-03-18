#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
  public:
    ExampleLayer() : Layer("ExampleLayer") {}

    void OnAttach() override { EDITOR_INFO("ExampleLayer::Attach"); }
    void OnDetach() override { EDITOR_INFO("ExampleLayer::Detach"); }
    void OnUpdate() override
    {
        if (Engine::Input::IsKeyPressed(ENGINE_KEY_TAB))
            EDITOR_INFO("Tab key is pressed");
    }
    void OnEvent(Engine::Event& event) override
    {
        if (event.GetEventType() == Engine::EventType::KeyPressed) {
            Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
            EDITOR_INFO("Key pressed: {0} ({1})", e.GetKeyCode(), (char)e.GetKeyCode());
        }
    }
};

class Editor : public Engine::Application
{
  public:
    Editor()
    {
        EDITOR_INFO("Editor constructor");
        PushLayer(new ExampleLayer());
        PushLayer(new Engine::ImGuiLayer());
    }
    ~Editor() { EDITOR_INFO("Editor destructor"); }
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Editor>();
}