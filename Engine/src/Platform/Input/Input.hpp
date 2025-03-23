#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class Input
{
  public:
    virtual ~Input()               = default;
    Input(const Input&)            = delete;
    Input& operator=(const Input&) = delete;

    static void Init();
    static void Shutdown();

  protected:
    Input() = default;

  public:
    static bool                      IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
    static bool                      IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
    static std::pair<double, double> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
    static double                    GetMouseX() { return s_Instance->GetMouseXImpl(); }
    static double                    GetMouseY() { return s_Instance->GetMouseYImpl(); }

  protected:
    virtual bool                      IsKeyPressedImpl(int keycode)        = 0;
    virtual bool                      IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<double, double> GetMousePositionImpl()               = 0;
    double                            GetMouseXImpl() { return GetMousePositionImpl().first; }
    double                            GetMouseYImpl() { return GetMousePositionImpl().second; }

  private:
    static std::unique_ptr<Input> s_Instance;
};
} // namespace Engine