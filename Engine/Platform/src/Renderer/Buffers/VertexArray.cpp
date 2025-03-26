#include "VertexArray.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLVertexArray.hpp"
#elif __linux__
#include "OpenGL/OpenGLVertexArray.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLVertexArray.hpp"
#endif

std::shared_ptr<Engine::VertexArray> Engine::VertexArray::Create()
{
#ifdef _WIN32
    return std::make_shared<OpenGLVertexArray>();
#elif __linux__
    return std::make_shared<OpenGLVertexArray>();
#elif __APPLE__
    return std::make_shared<OpenGLVertexArray>();
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}