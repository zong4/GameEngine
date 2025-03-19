#include "Application.hpp"

// Platform
#include "Core/Input/Input.hpp"
#include <glad/glad.h> // todo: unbind with opengl

Engine::Application* Engine::Application::s_Instance = nullptr;

void Engine::Application::Init()
{
    ENGINE_ASSERT(!s_Instance, "Application already exists");
    s_Instance = this;

    Input::Init();

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    // Vertex Array
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = {0, 1, 2};

    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running) {
        glClearColor(255, 0, 255, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->BeginRender();
        for (auto& layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->EndRender();

        m_Window->OnUpdate();
    }

    ENGINE_INFO("Application shutdown");
}

void Engine::Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(event);
        if (event.IsHandled()) {
            break;
        }
    }
}

bool Engine::Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}