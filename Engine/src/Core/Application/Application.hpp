#pragma once

#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"
#include "Core/Window/Window.hpp"

namespace Engine
{
class Application : public std::enable_shared_from_this<Application>
{
  public:
    Application();
    virtual ~Application();
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    void Run();
    void OnEvent(Event& e);

    template <typename T, typename... Args> void PushLayer(Args&&... args) { m_LayerStack.PushLayer(std::make_unique<T>(std::forward<Args>(args)...)); }
    template <typename T, typename... Args> void PushOverlay(Args&&... args) { m_LayerStack.PushOverlay(std::make_unique<T>(std::forward<Args>(args)...)); }

  public:
    static std::shared_ptr<Application> Get() { return s_Instance.lock(); }
    std::unique_ptr<Window>&            GetWindow() { return m_Window; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

  private:
    static std::weak_ptr<Application> s_Instance;
    std::unique_ptr<Window>           m_Window;
    LayerStack                        m_LayerStack;

    bool                                           m_Running   = true;
    bool                                           m_Minimized = false;
    std::chrono::high_resolution_clock::time_point m_LastFrameTime;
};

extern std::shared_ptr<Application> CreateApplication();
} // namespace Engine