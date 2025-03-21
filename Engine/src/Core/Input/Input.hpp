#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class Input
{
  public:
    Input()                        = default;
    virtual ~Input()               = default;
    Input(const Input&)            = delete;
    Input& operator=(const Input&) = delete;

    static void Init();

  public:
    inline static bool                      IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
    inline static bool                      IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
    inline static std::pair<double, double> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
    inline static double                    GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static double                    GetMouseY() { return s_Instance->GetMouseYImpl(); }

  protected:
    virtual bool                      IsKeyPressedImpl(int keycode)        = 0;
    virtual bool                      IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<double, double> GetMousePositionImpl()               = 0;
    virtual double                    GetMouseXImpl()                      = 0;
    virtual double                    GetMouseYImpl()                      = 0;

  private:
    static std::unique_ptr<Input> s_Instance;
};
} // namespace Engine