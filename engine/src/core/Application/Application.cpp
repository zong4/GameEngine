#include "Application.hpp"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Engine::Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running)
    {
        for (Layer *layer : m_LayerStack)
        {
            layer->OnUpdate();
        }

        m_Window->OnUpdate();
    }

    ENGINE_INFO("Application shutdown");
}

void Engine::Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.IsHandled())
        {
            break;
        }
    }
}

bool Engine::Application::OnWindowClose(WindowCloseEvent &e)
{
    m_Running = false;
    return true;
}