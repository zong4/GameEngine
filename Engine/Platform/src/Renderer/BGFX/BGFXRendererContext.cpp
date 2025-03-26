#include "BGFXRendererContext.hpp"

Engine::BGFXRendererContext::BGFXRendererContext(void* nativeWindow, bool vsync) : RendererContext(nativeWindow)
{
    bgfx::Init init_config;
    init_config.type = bgfx::RendererType::Count;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
    init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
    init.platformData.nwh = glfwGetWin32Window(window);
#endif

    int width, height;
    glfwGetWindowSize(static_cast<GLFWwindow*>(m_NativeWindow), &width, &height);
    init_config.resolution.width = (uint32_t)width;
    init_config.resolution.height = (uint32_t)height;
    init_config.resolution.reset = vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;

    if (!bgfx::init(init_config)) {
        const bgfx::RendererType::Enum rendererType = bgfx::getRendererType();
        Logger::EngineAssert(
            false,
            std::format("Failed to initialize BGFX renderer context of {0}", bgfx::getRendererName(rendererType)));
    }

    Logger::EngineInfo("BGFX renderer context is constructed");
}

Engine::BGFXRendererContext::~BGFXRendererContext()
{
    bgfx::shutdown();

    Logger::EngineInfo("BGFX renderer context is destructed");
}

void Engine::BGFXRendererContext::SwapBuffers()
{
    bgfx::frame();
}