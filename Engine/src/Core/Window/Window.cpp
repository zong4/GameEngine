#include "Window.hpp"

// Core
#include "Core/Renderer/Renderer.hpp"

// Platform
#include "Platform/GLFW/GLFWWindow.hpp"

std::unique_ptr<Engine::Window> Engine::Window::Create(const WindowProps& props)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return std::make_unique<GLFWWindow>(props);
    }
}