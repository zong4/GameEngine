#pragma once

#include "../Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine {
class BGFXWindow final : public Window
{
public:
    explicit BGFXWindow(const WindowProps& props);
    virtual ~BGFXWindow() override;

    void OnUpdate() override;
    void SetEventCallback(const std::function<void(Event&)>& callback) override;

public:
    virtual void* GetNativeWindow() const override { return m_Window; }
    virtual void SetVSync(bool enabled) override;

private:
    GLFWwindow* m_Window;
};
} // namespace Engine