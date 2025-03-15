#include <iostream>

#include <engine.hpp>

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        EDITOR_INFO("ExampleLayer::Update");
    }

    void OnEvent(Engine::Event &event) override
    {
        EDITOR_TRACE("{0}", event.ToString());
    }
};

class Editor : public Engine::Application
{
public:
    Editor()
    {
        EDITOR_INFO("Editor constructor");
        PushLayer(new ExampleLayer());
    }

    ~Editor()
    {
        EDITOR_INFO("Editor destructor");
    }
};

Engine::Application *Engine::CreateApplication()
{
    return new Editor();
}