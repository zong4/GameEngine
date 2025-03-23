#include "LayerStack.hpp"

void Engine::LayerStack::PopLayer(const std::string& name)
{
    auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&name](const std::unique_ptr<Layer>& layer) { return layer->GetName() == name; });
    if (it != m_Layers.begin() + m_LayerInsertIndex) {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void Engine::LayerStack::SetLayerActive(const std::string& name, bool active)
{
    auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&name](const std::unique_ptr<Layer>& layer) { return layer->GetName() == name; });
    if (it != m_Layers.end()) {
        it->get()->SetActive(active);
    }
}