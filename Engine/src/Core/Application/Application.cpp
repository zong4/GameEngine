#include "Application.hpp"

#include "Core/Input/Input.hpp"
#include "Core/Renderer/Renderer.hpp"
#include "Platform/ImGui/ImGuiLayer.hpp"

std::weak_ptr<Engine::Application> Engine::Application::s_Instance;

Engine::Application::Application()
{
    ENGINE_ASSERT(s_Instance.expired(), "Application already exists");
    s_Instance = std::static_pointer_cast<Application>(shared_from_this());

    m_Window = Window::Create();
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    Engine::Input::Init();
    Engine::Renderer::Init();

    ENGINE_INFO("Application is constructed");
}

Engine::Application::~Application()
{
    Engine::Renderer::Shutdown();
    Engine::Input::Shutdown();
    ENGINE_INFO("Application is destructed");
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application is running");

    m_LastFrameTime = std::chrono::high_resolution_clock::now();
    while (m_Running) {
        auto     now = std::chrono::high_resolution_clock::now();
        Timestep timestep(now - m_LastFrameTime);
        m_LastFrameTime = now;

        if (!m_Minimized) {
            for (auto& layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            ImGuiLayer::BeginRender();
            for (auto& layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            ImGuiLayer::EndRender();
        }

        m_Window->OnUpdate();
    }
}

void Engine::Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowResize));

    for (auto& layer : std::ranges::reverse_view(m_LayerStack)) {
        layer->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}

bool Engine::Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}

bool Engine::Application::OnWindowResize(WindowResizeEvent& e)
{
    m_Minimized = e.GetWidth() < 1 || e.GetHeight() < 1;

    if (!m_Minimized)
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}