#include "ImGuiLayer.hpp"

#include <imgui.h>

// Core
#include "../../Core/Application/Application.hpp"

// Platform
#include <glad/glad.h> // todo: unbind with opengl
#include "../Renderer/OpenGL/imgui_impl_opengl3.h"
#include "../Window/GLFW/imgui_impl_glfw.h" // todo: unbind with glfw
#include "../Window/GLFW/GLFWWindow.hpp"
#include "GLFW/glfw3.h"

void Engine::ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    void *native_window = Application::Get().GetWindow().GetNativeWindow();
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(native_window), true);
    ImGui_ImplOpenGL3_Init("#version 120");
}

void Engine::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ImGuiLayer::OnUpdate()
{
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine::ImGuiLayer::OnEvent(Event &event)
{
    ENGINE_INFO("{0}", event.ToString());

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool Engine::ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(event.GetMouseButton(), true);

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(event.GetMouseButton(), false);

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMousePosEvent(event.GetX(), event.GetY());

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), true);

    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    io.KeyCtrl = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftCtrl || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightCtrl;
    io.KeyShift = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftShift || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightShift;
    io.KeyAlt = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftAlt || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightAlt;
    io.KeySuper = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftSuper || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightSuper;

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), false);

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    int keycode = event.GetKeyCode();
    if (keycode > 0 && keycode < 0x10000)
    {
        io.AddInputCharacter((unsigned short)keycode);
    }

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}

bool Engine::ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());

    float x_scale, y_scale;
    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    glfwGetWindowContentScale(window, &x_scale, &y_scale);
    io.DisplayFramebufferScale = ImVec2(x_scale, y_scale);

    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }
    return false;
}
