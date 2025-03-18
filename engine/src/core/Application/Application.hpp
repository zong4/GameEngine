#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"

// Platform
#include "Platform/ImGui/ImGuiLayer.hpp"
#include "Platform/Window/Window.hpp"

namespace Engine
{
class Application
{
  public:
    Application() { Init(); }
    virtual ~Application()                     = default;
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    inline static Application& Get() { return *s_Instance; }
    inline Window&             GetWindow() { return *m_Window; }

    void Run();
    void OnEvent(Event& e);

    inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
    inline void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

  private:
    void Init();
    bool OnWindowClose(WindowCloseEvent& e);

  private:
    bool                    m_Running = true;
    std::unique_ptr<Window> m_Window; // todo: more windows
    ImGuiLayer*             m_ImGuiLayer;
    static Application*     s_Instance;

    LayerStack m_LayerStack;
};

extern std::unique_ptr<Application> CreateApplication();
} // namespace Engine