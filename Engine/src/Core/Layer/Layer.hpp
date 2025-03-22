#pragma once

#include "EnginePCH.hpp"

// tood: template to change files
class Event;

namespace Engine
{
class Layer
{
  public:
    Layer(const std::string& name = "Layer") : m_Name(name) {}
    virtual ~Layer() = default;

    virtual void OnUpdate(const Engine::Timestep& timestep) = 0;
    virtual void OnImGuiRender()                            = 0;
    virtual void OnEvent(Event& event)                      = 0;

  public:
    inline const std::string& GetName() const { return m_Name; }

  protected:
    std::string m_Name;
};
} // namespace Engine