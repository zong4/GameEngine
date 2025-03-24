#pragma once

#include "../Events/Event.hpp"
#include "../Time/Timestep.hpp"

namespace Engine {
class Layer
{
public:
    Layer(const std::string& name = "Layer") : m_Name(name) {}
    virtual ~Layer() = default;
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
    Layer(Layer&&) = default;
    Layer& operator=(Layer&&) = default;

    virtual void OnUpdate(const Engine::Timestep& timestep) = 0;
    virtual void OnImGuiRender() = 0;
    virtual void OnEvent(Event& event) = 0;

public:
    bool IsActive() const { return m_Active; }
    const std::string& GetName() const { return m_Name; }
    void SetActive(bool active) { m_Active = active; }
    void SetName(const std::string& name) { m_Name = name; }

protected:
    std::string m_Name;
    bool m_Active = true;
};
} // namespace Engine