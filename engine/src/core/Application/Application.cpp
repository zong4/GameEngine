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
        m_Window->OnUpdate();
    }

    ENGINE_INFO("Application shutdown");
}

void Engine::Application::OnEvent(Event &e)
{
    ENGINE_TRACE("{0}", e.ToString());

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
}

bool Engine::Application::OnWindowClose(WindowCloseEvent &e)
{
    m_Running = false;
    return true;
}