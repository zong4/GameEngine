#pragma once

#include "Platform/Input/Input.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
class GLFWInput final : public Input
{
  public:
    GLFWInput(void* window);
    virtual ~GLFWInput() override;

  protected:
    virtual bool                      IsKeyPressedImpl(int keycode) override;
    virtual bool                      IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<double, double> GetMousePositionImpl() override;

  private:
    GLFWwindow* GetGLFWWindow() const;

  private:
    GLFWwindow* m_Window = nullptr;
};
} // namespace Engine
