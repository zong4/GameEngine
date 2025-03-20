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

    virtual void OnAttach()            = 0;
    virtual void OnDetach()            = 0;
    virtual void OnUpdate()            = 0;
    virtual void BeginRender()         = 0;
    virtual void OnImGuiRender()       = 0;
    virtual void EndRender()           = 0;
    virtual void OnEvent(Event& event) = 0;

  public:
    inline const std::string& GetName() const { return m_DebugName; }

  protected:
    std::string m_DebugName;
};
} // namespace Engine