#pragma once

// Core
#include "Core/Input/Input.hpp"

namespace Engine
{
class GLFWInput : public Input
{
  public:
    GLFWInput();
    virtual ~GLFWInput();

  protected:
    virtual bool                      IsKeyPressedImpl(int keycode) override;
    virtual bool                      IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<double, double> GetMousePositionImpl() override;
    virtual double                    GetMouseXImpl() override;
    virtual double                    GetMouseYImpl() override;
};
} // namespace Engine
