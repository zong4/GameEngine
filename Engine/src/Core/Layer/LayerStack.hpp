#pragma once

#include "Core/Layer/Layer.hpp"

namespace Engine
{
class LayerStack
{
  public:
    ~LayerStack() = default;

    void PushLayer(std::shared_ptr<Layer> layer);
    void PushOverlay(std::shared_ptr<Layer> overlay);
    void PopLayer(std::shared_ptr<Layer> layer);
    void PopOverlay(std::shared_ptr<Layer> overlay);

  public:
    inline std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
    inline std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }

  private:
    unsigned int        m_LayerInsertIndex = 0;
    std::vector<std::shared_ptr<Layer>> m_Layers; // todo: use smart pointers
};
} // namespace Engine