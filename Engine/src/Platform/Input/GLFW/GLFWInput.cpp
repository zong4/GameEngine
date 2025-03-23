#include "GLFWInput.hpp"

#include "Core/Application/Application.hpp"

Engine::GLFWInput::GLFWInput(void* window) : m_Window(static_cast<GLFWwindow*>(window))
{
    Logger::EngineInfo(std::format("GLFWInput initialized (Window: {})", reinterpret_cast<void*>(m_Window)));
}

Engine::GLFWInput::~GLFWInput()
{
    Logger::EngineInfo("GLFW input system is destroyed");
}

GLFWwindow* Engine::GLFWInput::GetGLFWWindow() const
{
    return m_Window;
}

bool Engine::GLFWInput::IsKeyPressedImpl(int keycode)
{
    auto state = glfwGetKey(GetGLFWWindow(), keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Engine::GLFWInput::IsMouseButtonPressedImpl(int button)
{
    auto state = glfwGetMouseButton(GetGLFWWindow(), button);
    return state == GLFW_PRESS;
}

std::pair<double, double> Engine::GLFWInput::GetMousePositionImpl()
{
    double xpos, ypos;
    glfwGetCursorPos(GetGLFWWindow(), &xpos, &ypos);
    return {xpos, ypos};
}
