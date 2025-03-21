#pragma once

#include "Core/Layer/Layer.hpp"

class Event;

namespace Engine
{
class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    virtual ~ImGuiLayer();

    virtual void OnUpdate(Timestep timestep) override {}
    virtual void BeginRender() override;
    virtual void OnImGuiRender() override;
    virtual void EndRender() override;
    virtual void OnEvent(Event& event) override {}
};
}; // namespace Engine