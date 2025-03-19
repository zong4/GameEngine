#include "Application.hpp"

// Core
#include "Core/Input/Input.hpp"

// Platform
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

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
    };
    m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    uint32_t indices[3] = {0, 1, 2};
    m_IndexBuffer       = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        void main()
        {
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        void main()
        {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    m_Shader = Shader::Create(vertexSrc, fragmentSrc);
}

void Engine::Application::Run()
{
    ENGINE_INFO("Application running");

    while (m_Running) {
        glClearColor(255, 0, 255, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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