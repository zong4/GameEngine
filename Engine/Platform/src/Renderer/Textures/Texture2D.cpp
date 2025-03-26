#include "Texture2D.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLTexture2D.hpp"
#elif __linux__
#include "OpenGL/OpenGLTexture2D.hpp"
#elif __APPLE__
#include "OpenGL/OpenGLTexture2D.hpp"
#endif

std::shared_ptr<Engine::Texture2D> Engine::Texture2D::Create(uint32_t width, uint32_t height)
{
#ifdef _WIN32
    return std::make_shared<OpenGLTexture2D>(width, height);
#elif __linux__
    return std::make_shared<OpenGLTexture2D>(width, height);
#elif __APPLE__
    return std::make_shared<OpenGLTexture2D>(width, height);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}

std::shared_ptr<Engine::Texture2D> Engine::Texture2D::Create(const std::string& path)
{
#ifdef _WIN32
    return std::make_shared<OpenGLTexture2D>(path);
#elif __linux__
    return std::make_shared<OpenGLTexture2D>(path);
#elif __APPLE__
    return std::make_shared<OpenGLTexture2D>(path);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}
