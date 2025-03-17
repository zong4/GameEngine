#pragma once

// Core
#include "../../Core/Layer/Layer.hpp"
#include "../../Core/Events/ApplicationEvent.hpp"
#include "../../Core/Events/KeyEvent.hpp"
#include "../../Core/Events/MouseEvent.hpp"

namespace Engine
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() : Layer("ImGuiLayer") {}
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
        bool OnMouseMovedEvent(MouseMovedEvent &event);
        bool OnMouseScrolledEvent(MouseScrolledEvent &event);
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnKeyReleasedEvent(KeyReleasedEvent &event);
        bool OnKeyTypedEvent(KeyTypedEvent &event);
        bool OnWindowResizeEvent(WindowResizeEvent &event);

    private:
        float m_Time = 0.0f;
    };
}; // namespace Engine