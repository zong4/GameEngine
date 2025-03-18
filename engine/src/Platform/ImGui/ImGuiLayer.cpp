#include "ImGuiLayer.hpp"

// Core
#include "Core/Application/Application.hpp"

// Platform
#include "Platform/Window/GLFW/GLFWWindow.hpp"

// Functions
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

void Engine::ImGuiLayer::OnAttach()
{
    // Set up ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Set up ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Set up platform/renderer bindings
    void* native_window = Application::Get().GetWindow().GetNativeWindow();
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(native_window), true);
    ImGui_ImplOpenGL3_Init("#version 120");
}

void Engine::ImGuiLayer::BeginRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGuiLayer::OnImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void Engine::ImGuiLayer::EndRender()
{
    ImGuiIO&     io  = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize =
        ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Engine::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}