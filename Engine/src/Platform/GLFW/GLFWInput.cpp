#include "GLFWInput.hpp"

// Core
#include "Core/Application/Application.hpp"

// Platform
#include <GLFW/glfw3.h>

bool Engine::GLFWInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow*>(Engine::Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Engine::GLFWInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow*>(Engine::Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Engine::GLFWInput::GetMousePositionImpl()
{
    auto   window = static_cast<GLFWwindow*>(Engine::Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

float Engine::GLFWInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float Engine::GLFWInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}