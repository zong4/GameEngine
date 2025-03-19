#include "Renderer.hpp"

#ifdef PLATFORM_WINDOWS
Engine::RendererAPI Engine::Renderer::s_RendererAPI = Engine::RendererAPI::OpenGL;
#elif PLATFORM_LINUX
Engine::RendererAPI Engine::Renderer::s_RendererAPI = Engine::RendererAPI::OpenGL;
#elif PLATFORM_MACOSX
Engine::RendererAPI Engine::Renderer::s_RendererAPI = Engine::RendererAPI::OpenGL;
#endif