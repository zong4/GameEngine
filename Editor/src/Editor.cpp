#include "Editor.hpp"

#include "EditorLayer2D.hpp"

void Editor::Init()
{
    Application::Init();
    GetLayerStack().PushLayer<EditorLayer2D>();
    GetLayerStack().PushOverlay<Engine::ImGuiLayer>();

    Engine::Logger::EditorInfo("Editor is initialized");
}

void Editor::Run()
{
    Application::Run();
}

void Editor::Shutdown()
{
    Application::Shutdown();

    Engine::Logger::EditorInfo("Editor is shutdown");
}

std::unique_ptr<Engine::Application>& Engine::Application::Create()
{
    s_Instance = std::make_unique<Editor>();
    return Application::Get();
}