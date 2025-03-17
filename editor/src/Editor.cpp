#include <memory>

#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer() : Layer("ExampleLayer") {}

    void OnAttach() override
    {
        EDITOR_INFO("ExampleLayer::Attach");
    }

    void OnDetach() override
    {
        EDITOR_INFO("ExampleLayer::Detach");
    }

    void OnUpdate() override
    {
    }

    void OnEvent(Engine::Event &event) override
    {
        EDITOR_INFO("{0}", event.ToString());
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

    ~Editor()
    {
        EDITOR_INFO("Editor destructor");
    }
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Editor>();
}