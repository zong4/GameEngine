#include "GLFWInput.hpp"

Engine::GLFWInput::GLFWInput(void* window) : Input(window)
{
    Logger::EngineInfo(std::format("GLFWInput initialized (Window: {})", m_Window));
}

Engine::GLFWInput::~GLFWInput()
{
    Logger::EngineInfo("GLFW input system is destroyed");
}

GLFWwindow* Engine::GLFWInput::GetGLFWWindow() const
{
    return static_cast<GLFWwindow*>(m_Window);
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
