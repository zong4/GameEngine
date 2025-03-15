#pragma once

#include <GLFW/glfw3.h>

#include "Window.hpp"

namespace Engine
{
    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProps &props);
        virtual ~GLFWWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const std::function<void(Event &)> &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();

    private:
        GLFWwindow *m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            std::function<void(Event &)> EventCallback;
        };

        WindowData m_Data;
    };
} // namespace Engine