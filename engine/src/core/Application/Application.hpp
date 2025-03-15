#pragma once

#include <GLFW/glfw3.h>

#include "../Core.hpp"
#include "../Window/Window.hpp"
#include "../Events/ApplicationEvent.hpp"
#include "../Events/KeyEvent.hpp"
#include "../Events/MouseEvent.hpp"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();
        void OnEvent(Event &e);

    private:
        bool OnWindowClose(WindowCloseEvent &e);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    extern Application *CreateApplication();
} // namespace Engine