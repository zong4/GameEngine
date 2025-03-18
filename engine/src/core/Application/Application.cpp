#include "Application.hpp"

// Platform
#include "Platform/Input/Input.hpp"
#include <glad/glad.h> // todo: unbind with opengl

Engine::Application* Engine::Application::s_Instance = nullptr;

void Engine::Application::Init()
{
    ENGINE_ASSERT(!s_Instance, "Application already exists");
    s_Instance = this;

    Input::Init();

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running) {
        glClearColor(255, 0, 255, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->BeginRender();
        for (auto& layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->EndRender();

        m_Window->OnUpdate();
    }

    ENGINE_INFO("Application shutdown");
}

void Engine::Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(event);
        if (event.IsHandled()) {
            break;
        }
    }
}

bool Engine::Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}