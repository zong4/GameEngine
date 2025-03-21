#include "ExampleLayer.hpp"

class Editor : public Engine::Application
{
  public:
    Editor()
    {
        Engine::Input::Init();
        Engine::Renderer::Init();

        PushLayer(new ExampleLayer());
        PushOverlay(new Engine::ImGuiLayer());

        EDITOR_INFO("Editor is initialized");
    }
    ~Editor() { EDITOR_INFO("Editor is shutdown"); }
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Editor>();
}