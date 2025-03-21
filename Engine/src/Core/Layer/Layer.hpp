#pragma once

#include "EnginePCH.hpp"

// tood: template to change files
class Event;

namespace Engine
{
class Layer
{
  public:
    Layer(const std::string& name = "Layer") : m_DebugName(name) {}
    virtual ~Layer() = default;

    virtual void OnUpdate(Timestep timestep) = 0;
    virtual void OnImGuiRender()             = 0;
    virtual void OnEvent(Event& event)       = 0;

  public:
    inline const std::string& GetName() const { return m_DebugName; }

  protected:
    std::string m_DebugName;
};
} // namespace Engine