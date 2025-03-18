#pragma once

#include "EnginePCH.hpp"

// Core
#include "Core/Layer/Layer.hpp"

namespace Engine
{
class LayerStack
{
  public:
    LayerStack() = default;
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

  private:
    std::vector<Layer*> m_Layers;
    unsigned int        m_LayerInsertIndex = 0;
};
} // namespace Engine