#pragma once

#include <GLFW/glfw3.h>

#include "../Core.hpp"
#include "../Window/Window.hpp"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    extern Application *CreateApplication();
} // namespace Engine