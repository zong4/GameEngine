#include "Application.hpp"

#include "Core/Renderer/Renderer.hpp"
#include <GLFW/glfw3.h> // todo: remove

std::unique_ptr<Engine::Application> Engine::Application::s_Instance = nullptr;

Engine::Application::Application()
{
    ENGINE_ASSERT(!s_Instance, "4Application already exists");
    s_Instance.reset(this);

    m_Window = Window::Create();
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    ENGINE_INFO("Application is initialized");
}

Engine::Application::~Application()
{
    s_Instance.release();
    ENGINE_INFO("Application shutdown");
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");
    while (m_Running) {
        float    time     = static_cast<float>(glfwGetTime());
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime   = time;

        if (!m_Minimized) {
            for (auto& layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }
        }

        
            m_ImGuilayer->BeginRender();
        for (auto& layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuilayer->EndRender();

            m_Window->OnUpdate();
    }
}

void Engine::Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowResize));

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

bool Engine::Application::OnWindowResize(WindowResizeEvent& e)
{
    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }
    m_Minimized = false;

    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}