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
     void BeginRender();
    virtual void OnImGuiRender() override;
     void EndRender();
    virtual void OnEvent(Event& event) override {}
};
}; // namespace Engine