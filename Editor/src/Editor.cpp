#include "Editor.hpp"

#include "EditorLayer2D.hpp"

void Editor::Init()
{
    Application::Init();

    GetLayerStack().PushLayer<EditorLayer2D>();

    Engine::Logger::EditorInfo("Editor is initialized");
}

void Editor::Run()
{
    Application::Run();
}

void Editor::Shutdown()
{
    Engine::Logger::EditorInfo("Editor is shutdown");

    for (int i = static_cast<int>(GetLayerStack().size()) - 1; i >= 0; i--) {
        GetLayerStack().PopLayer(i);
    }

    Application::Shutdown();
}

std::unique_ptr<Engine::Application>& Engine::Application::Create()
{
    s_Instance = std::make_unique<Editor>();
    return Application::Get();
}