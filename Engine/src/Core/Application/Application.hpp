#pragma once

#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"
#include "Core/Window/Window.hpp"

namespace Engine
{
class Application
{
  public:
    Application()                              = default;
    virtual ~Application()                     = default;
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    virtual void Init();
    virtual void Run();
    virtual void Shutdown();
    void         OnEvent(Event& e);

    template <typename T, typename... Args> void PushLayer(Args&&... args) { m_LayerStack.PushLayer(std::make_unique<T>(std::forward<Args>(args)...)); }
    template <typename T, typename... Args> void PushOverlay(Args&&... args) { m_LayerStack.PushOverlay(std::make_unique<T>(std::forward<Args>(args)...)); }

    static std::unique_ptr<Application>& Create();

  public:
    static std::unique_ptr<Application>& Get() { return s_Instance; }
    std::unique_ptr<Window>&             GetWindow() { return m_Window; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

  private:
    static std::unique_ptr<Application> s_Instance;
    std::unique_ptr<Window>             m_Window;
    LayerStack                          m_LayerStack;

    bool                                           m_Running   = true;
    bool                                           m_Minimized = false;
    std::chrono::high_resolution_clock::time_point m_LastFrameTime;
};
} // namespace Engine