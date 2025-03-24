#include "Application.hpp"

std::unique_ptr<Engine::Application> Engine::Application::s_Instance = nullptr;

void Engine::Application::Init()
{
    Engine::Logger::Init();

    m_Window = Window::Create({"Game Engine", 1280, 720});
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    Engine::Input::Init(m_Window->GetNativeWindow());
    Engine::Renderer::Init();

    GetLayerStack().PushOverlay<Engine::ImGuiLayer>(
        m_Window->GetNativeWindow());

    Logger::EngineInfo("Application is initialized");
}

void Engine::Application::Run()
{
    Logger::EngineInfo("Application is running");

    m_LastFrameTime = std::chrono::high_resolution_clock::now();
    while (m_Running)
    {
        auto now = std::chrono::high_resolution_clock::now();
        Timestep timestep(now - m_LastFrameTime);
        m_LastFrameTime = now;

        if (!m_Minimized)
        {
            for (auto& layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            ImGuiLayer::BeginRender();
            for (auto& layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            ImGuiLayer::EndRender(static_cast<float>(m_Window->GetWidth()),
                                  static_cast<float>(m_Window->GetHeight()));
        }

        m_Window->OnUpdate();
    }
}

void Engine::Application::Shutdown()
{
    Engine::Renderer::Shutdown();
    Engine::Input::Shutdown();

    m_Window.reset();

    Logger::EngineInfo("Application is shutdown");
    Logger::Shutdown();
}

void Engine::Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(
        ENGINE_BIND_EVENT_FN(Application::OnWindowResize));

    for (auto& layer : std::ranges::reverse_view(m_LayerStack))
    {
        layer->OnEvent(event);
        if (event.IsHandled())
        {
            break;
        }
    }
}

bool Engine::Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;

    Logger::EngineTrace("Window close event is handled in Application");
    return true;
}

bool Engine::Application::OnWindowResize(WindowResizeEvent& e)
{
    m_Minimized = e.GetWidth() < 1 || e.GetHeight() < 1;

    if (!m_Minimized)
    {
        Renderer::OnWindowResize(static_cast<uint32_t>(e.GetWidth()),
                                 static_cast<uint32_t>(e.GetHeight()));
    }

    Logger::EngineTrace("Window resize event is handled in Application");
    return false;
}