#include "GLFWInput.hpp"

// Core
#include "Core/Application/Application.hpp"

// Platform
#include <GLFW/glfw3.h>

Engine::GLFWInput::GLFWInput()
{
    ENGINE_INFO("GLFW input system is initialized");
}

Engine::GLFWInput::~GLFWInput()
{
    ENGINE_INFO("GLFW input system is destroyed");
}

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

std::pair<double, double> Engine::GLFWInput::GetMousePositionImpl()
{
    auto   window = static_cast<GLFWwindow*>(Engine::Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

double Engine::GLFWInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

double Engine::GLFWInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}