#include "Application.hpp"

// Core
#include "Core/Input/Input.hpp"

// Platform
#include <glad/glad.h> // todo: unbind with opengl

// todo: change location
static GLint ShaderDataTypeToOpenGLBaseType(Engine::ShaderDataType type)
{
    switch (type) {
    case Engine::ShaderDataType::Float:
    case Engine::ShaderDataType::Float2:
    case Engine::ShaderDataType::Float3:
    case Engine::ShaderDataType::Float4:
    case Engine::ShaderDataType::Mat3:
    case Engine::ShaderDataType::Mat4:
        return GL_FLOAT;
    case Engine::ShaderDataType::Int:
    case Engine::ShaderDataType::Int2:
    case Engine::ShaderDataType::Int3:
    case Engine::ShaderDataType::Int4:
        return GL_INT;
    case Engine::ShaderDataType::Bool:
        return GL_BOOL;
    default:
        ENGINE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
}

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application()
{
    ENGINE_ASSERT(!s_Instance, "Application already exists");
    s_Instance = this;

    // Initialize core systems
    {
        Input::Init();

        m_Window = Window::Create();
        m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));
    }
    ENGINE_INFO("Application is initialized");

    // todo: remove
    {
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
            0.8f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f,
        };
        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);

        uint32_t index = 0;
        for (auto& element : m_VertexBuffer->GetLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.GetType()),
                                  element.GetNormalized() ? GL_TRUE : GL_FALSE, m_VertexBuffer->GetLayout().GetStride(),
                                  reinterpret_cast<const void*>(static_cast<uintptr_t>(element.GetOffset())));
            index++;
        }

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer       = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

        std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position, 1.0);
        }
    )";

        m_Shader = Shader::Create(vertexSrc, fragmentSrc);
    }
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

        // todo: not sure about the sort
        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }
        for (auto& layer : m_LayerStack) {
            layer->BeginRender();
            layer->OnImGuiRender();
            layer->EndRender();
        }
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