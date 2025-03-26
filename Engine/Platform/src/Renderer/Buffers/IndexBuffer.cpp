#include "IndexBuffer.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLIndexBuffer.hpp"
#elif __linux__
#include "OpenGL/OpenGLIndexBuffer.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLIndexBuffer.hpp"
#endif

std::shared_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(uint32_t size)
{
#ifdef _WIN32
    return std::make_shared<OpenGLIndexBuffer>(size);
#elif __linux__
    return std::make_shared<OpenGLIndexBuffer>(size);
#elif __APPLE__
    return std::make_shared<OpenGLIndexBuffer>(size);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}

std::shared_ptr<Engine::IndexBuffer> Engine::IndexBuffer::Create(std::span<uint32_t> indices)
{
#ifdef _WIN32
    return std::make_shared<OpenGLIndexBuffer>(indices);
#elif __linux__
    return std::make_shared<OpenGLIndexBuffer>(indices);
#elif __APPLE__
    return std::make_shared<OpenGLIndexBuffer>(indices);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}