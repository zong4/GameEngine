#pragma once

// Core
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/MouseEvent.hpp"
#include "Core/Layer/Layer.hpp"

namespace Engine
{
class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer() : Layer("ImGuiLayer") {}
    virtual ~ImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnUpdate() override {}
    virtual void BeginRender() override;
    virtual void OnImGuiRender() override;
    virtual void EndRender() override;
    virtual void OnEvent(Event& event) override {}
    virtual void OnDetach() override;
};
}; // namespace Engine