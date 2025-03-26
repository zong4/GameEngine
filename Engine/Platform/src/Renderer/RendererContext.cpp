#include "RendererContext.hpp"

#ifdef _WIN32
#include "OpenGL/OpenGLRendererContext.hpp"
#elif __linux__
#include "OpenGL/OpenGLRendererContext.hpp"
#elif __APPLE__
#include "BGFX/BGFXRendererContext.hpp"
#endif

std::unique_ptr<Engine::RendererContext> Engine::RendererContext::Create(void* nativeWindow, bool vsync)
{
#ifdef _WIN32
    return std::make_unique<OpenGLRendererContext>(nativeWindow, vsync);
#elif __linux__
    return std::make_unique<OpenGLRendererContext>(nativeWindow, vsync);
#elif __APPLE__
    return std::make_unique<BGFXRendererContext>(nativeWindow, vsync);
#endif

    Logger::EngineAssert(false, "Unknown Platform");
    return nullptr;
}