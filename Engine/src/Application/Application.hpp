#pragma once

#include <functions.hpp>

namespace Engine
{
class Application
{
public:
    Application() = default;
    virtual ~Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    virtual void Init();
    virtual void Run();
    virtual void Shutdown();
    void OnEvent(Event& e);

    static std::unique_ptr<Application>& Create();

public:
    static std::unique_ptr<Application>& Get() { return s_Instance; }
    std::unique_ptr<Window>& GetWindow() { return m_Window; }
    LayerStack& GetLayerStack() { return m_LayerStack; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

private:
    static std::unique_ptr<Application> s_Instance;
    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;

    bool m_Running = true;
    bool m_Minimized = false;
    std::chrono::high_resolution_clock::time_point m_LastFrameTime;
};
} // namespace Engine