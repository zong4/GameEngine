#include "LayerStack.hpp"

Engine::LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers) {
        layer->OnDetach();
        delete layer;
    }
}

void Engine::LayerStack::PushLayer(Layer* layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
    layer->OnAttach();
    ENGINE_INFO("Layer {0} is pushed", layer->GetName());
}

void Engine::LayerStack::PushOverlay(Layer* overlay)
{
    m_Layers.emplace_back(overlay);
    overlay->OnAttach();
    ENGINE_INFO("Overlay {0} is pushed", overlay->GetName());
}

void Engine::LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        layer->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
    ENGINE_INFO("Layer {0} is popped", layer->GetName());
}

void Engine::LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        overlay->OnDetach();
        m_Layers.erase(it);
    }
    ENGINE_INFO("Overlay {0} is popped", overlay->GetName());
}