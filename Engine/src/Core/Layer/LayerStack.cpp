#include "LayerStack.hpp"

void Engine::LayerStack::PushLayer(std::shared_ptr<Layer> layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
    ENGINE_INFO("Layer {0} is pushed", layer->GetName());
}

void Engine::LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
{
    m_Layers.emplace_back(overlay);
    ENGINE_INFO("Overlay {0} is pushed", overlay->GetName());
}

void Engine::LayerStack::PopLayer(std::shared_ptr<Layer> layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
    ENGINE_INFO("Layer {0} is popped", layer->GetName());
}

void Engine::LayerStack::PopOverlay(std::shared_ptr<Layer> overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
    }
    ENGINE_INFO("Overlay {0} is popped", overlay->GetName());
}