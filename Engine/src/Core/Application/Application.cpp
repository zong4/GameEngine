#include "Application.hpp"

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application()
{
    ENGINE_ASSERT(!s_Instance, "Application already exists");
    s_Instance = this;

    m_Window = Window::Create();
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    ENGINE_INFO("Application is initialized");
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");
    while (m_Running) {
        // todo: not sure about the sort
        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }
        for (auto& layer : m_LayerStack) {
            layer->BeginRender();
            layer->OnImGuiRender();
            layer->EndRender();
        }
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