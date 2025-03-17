#include "ImGuiLayer.hpp"

#include <imgui.h>

// Core
#include "../../Core/Application/Application.hpp"

// Platform
#include <glad/glad.h> // todo: unbind with opengl
#include "../Renderer/OpenGL/imgui_impl_opengl3.h"
#include "../Window/GLFW/imgui_impl_glfw.h" // todo: unbind with glfw
#include "../Window/GLFW/GLFWWindow.hpp"

void Engine::ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 120");
}

void Engine::ImGuiLayer::OnDetach()
{
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

    return false;
}

bool Engine::ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(event.GetMouseButton(), false);

    return false;
}

bool Engine::ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMousePosEvent(event.GetX(), event.GetY());

    return false;
}

bool Engine::ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());

    return false;
}

bool Engine::ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), true);

    io.KeyCtrl = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftCtrl || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightCtrl;
    io.KeyShift = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftShift || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightShift;
    io.KeyAlt = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftAlt || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightAlt;
    io.KeySuper = (ImGuiKey)event.GetKeyCode() == ImGuiKey_LeftSuper || (ImGuiKey)event.GetKeyCode() == ImGuiKey_RightSuper;

    return false;
}

bool Engine::ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), false);

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

    return false;
}

bool Engine::ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    glViewport(0, 0, event.GetWidth(), event.GetHeight());

    return false;
}
