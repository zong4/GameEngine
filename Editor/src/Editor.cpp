#include "Editor.hpp"

#include "EditorLayer2D.hpp"

void Editor::Init()
{
    Application::Init();
    PushLayer<EditorLayer2D>();
    PushOverlay<Engine::ImGuiLayer>();
}

void Editor::Run()
{
    Application::Run();
}

void Editor::Shutdown()
{
    Application::Shutdown();
}

std::unique_ptr<Engine::Application>& Engine::Application::Create()
{
    s_Instance = std::make_unique<Editor>();
    return Application::Get();
}