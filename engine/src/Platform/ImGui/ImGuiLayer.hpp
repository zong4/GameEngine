#pragma once

#include "../../EnginePCH.hpp"
#include "../../Core/Layer/Layer.hpp"

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
        float m_Time = 0.0f;
    };
}; // namespace Engine