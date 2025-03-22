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

    virtual void OnUpdate(const Engine::Timestep& timestep) override {}
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override {}

    static void BeginRender();
    static void EndRender();
};
}; // namespace Engine