#pragma once

#include "Layer.hpp"

namespace Engine
{
class LayerStack
{
  public:
    ~LayerStack() = default;

    template <typename T, typename... Args> void PushLayer(Args&&... args)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::make_unique<T>(std::forward<Args>(args)...));
        m_LayerInsertIndex++;
    }
    template <typename T, typename... Args> void PushOverlay(Args&&... args) { m_Layers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)); }
    void                                         PopLayer(std::size_t index);
    void                                         PopLayer(const std::string& name);

  public:
    auto        begin() { return m_Layers.begin(); }
    auto        end() { return m_Layers.end(); }
    auto        begin() const { return m_Layers.cbegin(); }
    auto        end() const { return m_Layers.cend(); }
    std::size_t size() const { return m_Layers.size(); }

    std::size_t GetLayerInsertIndex() const { return m_LayerInsertIndex; }
    void        SetLayerActive(const std::string& name, bool active);

  private:
    std::size_t                         m_LayerInsertIndex = 0;
    std::vector<std::unique_ptr<Layer>> m_Layers;
};
} // namespace Engine