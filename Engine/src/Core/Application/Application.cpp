#include "Application.hpp"

// Core
#include "Core/Input/Input.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Renderer.hpp"

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
        m_VertexArray = VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
            0.8f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f,
        };
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t                     indices[3]  = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

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
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();

        Renderer::BeginScene();
        {
            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);
        }
        Renderer::EndScene();

        RenderCommand::DrawIndexed(m_VertexArray);

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