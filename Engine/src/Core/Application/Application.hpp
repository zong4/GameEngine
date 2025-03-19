#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"
#include "Core/Window/Window.hpp"

// Platform
#include "Platform/ImGui/ImGuiLayer.hpp"

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
    static Application* s_Instance;

    bool                    m_Running = true;
    std::unique_ptr<Window> m_Window; // todo: more windows

    ImGuiLayer* m_ImGuiLayer;
    LayerStack  m_LayerStack;

    unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
};

extern std::unique_ptr<Application> CreateApplication();
} // namespace Engine