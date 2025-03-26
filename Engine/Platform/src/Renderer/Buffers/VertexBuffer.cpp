#include "VertexBuffer.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLVertexBuffer.hpp"
#elif __linux__
#include "OpenGL/OpenGLVertexBuffer.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLVertexBuffer.hpp"
#endif

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(uint32_t size)
{
#ifdef _WIN32
    return std::make_shared<OpenGLVertexBuffer>(size);
#elif __linux__
    return std::make_shared<OpenGLVertexBuffer>(size);
#elif __APPLE__
    return std::make_shared<OpenGLVertexBuffer>(size);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(std::span<const float> vertices, BufferLayout layout)
{
#ifdef _WIN32
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#elif __linux__
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#elif __APPLE__
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}

std::shared_ptr<Engine::VertexBuffer> Engine::VertexBuffer::Create(std::span<const double> vertices,
                                                                   BufferLayout layout)
{
#ifdef _WIN32
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#elif __linux__
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#elif __APPLE__
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}