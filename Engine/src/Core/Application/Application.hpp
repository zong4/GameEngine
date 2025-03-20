#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Layer/LayerStack.hpp"
#include "Core/Renderer/BufferLayout.hpp"
#include "Core/Renderer/IndexBuffer.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Renderer/VertexBuffer.hpp"
#include "Core/Window/Window.hpp"

namespace Engine
{
class Application
{
  public:
    Application();
    virtual ~Application()                     = default;
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    void Run();
    void OnEvent(Event& e);

    inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
    inline void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

  public:
    inline static Application& Get() { return *s_Instance; }
    inline Window&             GetWindow() { return *m_Window; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);

  private:
    static Application* s_Instance;

    bool                    m_Running = true;
    std::unique_ptr<Window> m_Window; // todo: more windows
    LayerStack              m_LayerStack;

    // Renderer
    unsigned int                  m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer>  m_IndexBuffer;
    std::unique_ptr<Shader>       m_Shader;
};

extern std::unique_ptr<Application> CreateApplication();
} // namespace Engine