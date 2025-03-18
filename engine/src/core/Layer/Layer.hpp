#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Events/Event.hpp"

namespace Engine
{
class Layer
{
  public:
    Layer(const std::string& name = "Layer") : m_DebugName(name) {}
    virtual ~Layer() = default;

    inline const std::string& GetName() const { return m_DebugName; }

    virtual void OnAttach()            = 0;
    virtual void OnDetach()            = 0;
    virtual void OnUpdate()            = 0;
    virtual void OnEvent(Event& event) = 0;

  protected:
    std::string m_DebugName;
};
} // namespace Engine