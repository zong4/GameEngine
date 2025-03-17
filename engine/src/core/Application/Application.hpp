#pragma once

#include "../../EnginePCH.hpp"
#include <GLFW/glfw3.h>

#include "../../Platform/Window/Window.hpp"
#include "../Events/ApplicationEvent.hpp"
#include "../Layer/LayerStack.hpp"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();
        void OnEvent(Event &e);

        inline void PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }
        inline void PushOverlay(Layer *overlay) { m_LayerStack.PushOverlay(overlay); }

    private:
        bool OnWindowClose(WindowCloseEvent &e);

    private:
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;

        LayerStack m_LayerStack;
    };

    extern Application *CreateApplication();
} // namespace Engine