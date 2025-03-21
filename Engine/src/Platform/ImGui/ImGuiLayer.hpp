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
    ImGuiLayer();
    virtual ~ImGuiLayer();

    virtual void OnUpdate() override {}
    virtual void BeginRender() override;
    virtual void OnImGuiRender() override;
    virtual void EndRender() override;
    virtual void OnEvent(Event& event) override {}
};
}; // namespace Engine