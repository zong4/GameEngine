#include "Editor2D.hpp"

class Editor : public Engine::Application
{
  public:
    Editor() : Engine::Application()
    {
        PushLayer<Editor2D>();
        PushOverlay<Engine::ImGuiLayer>();

        EDITOR_INFO("Editor is constructed");
    }
    virtual ~Editor() noexcept override = default;
};

std::shared_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_shared<Editor>();
}