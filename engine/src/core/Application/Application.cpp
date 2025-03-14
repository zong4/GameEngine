#include "Application.hpp"

Engine::Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->OnUpdate();
    }

    ENGINE_INFO("Application shutdown");
}