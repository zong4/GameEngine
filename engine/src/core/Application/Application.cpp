#include "Application.hpp"

#include <glad/glad.h>

Engine::Application *Engine::Application::s_Instance = nullptr;

Engine::Application::Application()
{
    ENGINE_ASSERT(!s_Instance, "Application already exists");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running)
    {
        glClearColor(255, 0, 255, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto &layer : m_LayerStack)
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
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

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