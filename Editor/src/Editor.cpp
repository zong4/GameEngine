#include "Editor2D.hpp"

class Editor : public Engine::Application
{
  public:
      Editor()
      {
    }

      void Init() override
    {
        Application::Init();
        PushLayer<Editor2D>();
        PushOverlay<Engine::ImGuiLayer>();
    }

      virtual ~Editor() noexcept override
      { 
    }

      void Shutdown() override { Application::Shutdown(); }
};

std::unique_ptr<Engine::Application>& Engine::Application::Create()
{
    s_Instance = std::make_unique<Editor>();
    return Application::Get();
}