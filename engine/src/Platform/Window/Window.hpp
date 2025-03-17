#pragma once

#include "../../EnginePCH.hpp"

// Core
#include "../../Core/Events/Event.hpp"

namespace Engine
{
    /// @brief Properties for a window
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "Game Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    /// @brief Interface representing a desktop system based Window
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual void *GetNativeWindow() const = 0;

        virtual void SetEventCallback(const std::function<void(Event &)> &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        /// @brief Creates a window
        /// @param props The properties of the window
        /// @return A pointer to the window
        static Window *Create(const WindowProps &props = WindowProps());
    };
} // namespace Engine