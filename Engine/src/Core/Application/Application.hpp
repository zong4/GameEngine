#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"
#include "Core/Window/Window.hpp"
#include "Platform/ImGui/ImGuiLayer.hpp"

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

    inline void PushLayer(std::shared_ptr<Layer> layer) { m_LayerStack.PushLayer(layer); }
    inline void PushOverlay(std::shared_ptr<Layer> overlay) { m_LayerStack.PushOverlay(overlay); }

  public:
    inline static std::unique_ptr<Application>& Get() { return s_Instance; }
    inline std::unique_ptr<Window>&             GetWindow() { return m_Window; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

  private:
    static std::unique_ptr<Application> s_Instance;

    bool                        m_Running = true;
    bool                        m_Minimized = false;

    std::unique_ptr<Window>     m_Window; // todo: more windows
    LayerStack                  m_LayerStack;
    std::unique_ptr<ImGuiLayer> m_ImGuilayer;

    float m_LastFrameTime = 0.0f;
};

extern std::unique_ptr<Application> CreateApplication();
} // namespace Engine