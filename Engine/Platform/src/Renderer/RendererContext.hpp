#pragma once

#include <core.hpp>

namespace Engine {
class RendererContext
{
public:
    virtual ~RendererContext() = default;

    virtual void SwapBuffers() = 0;

    static std::unique_ptr<Engine::RendererContext> Create(void* nativeWindow, bool vsync);

protected:
    RendererContext(void* nativeWindow) : m_NativeWindow(nativeWindow) {}

protected:
    void* m_NativeWindow;
};
} // namespace Engine