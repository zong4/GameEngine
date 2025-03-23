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
    Engine::Logger::EditorInfo("Editor is shutdown");

    for (std::size_t i = GetLayerStack().GetLayerInsertIndex() - 1; i >= 0; i--) {
        GetLayerStack().PopLayer(i);
    }

    Application::Shutdown();
}

std::unique_ptr<Engine::Application>& Engine::Application::Create()
{
    s_Instance = std::make_unique<Editor>();
    return Application::Get();
}