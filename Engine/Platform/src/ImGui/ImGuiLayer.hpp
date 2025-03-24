#pragma once

#include <core.hpp>

namespace Engine
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(void* window);
    virtual ~ImGuiLayer();

    virtual void OnUpdate(const Engine::Timestep& timestep) override {}
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override {}

    static void BeginRender();
    static void EndRender(float width, float height);

private:
    void* m_Window;
};
}; // namespace Engine