#pragma once

#include "../Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine {
class VulkanWindow final : public Window
{
public:
    explicit VulkanWindow(const WindowProps& props);
    virtual ~VulkanWindow() override;

    void OnUpdate() override;
    void SetEventCallback(const std::function<void(Event&)>& callback) override;

public:
    virtual void* GetNativeWindow() const override { return m_Window; }
    virtual void SetVSync(bool enabled) override;

private:
    GLFWwindow* m_Window;
};
} // namespace Engine