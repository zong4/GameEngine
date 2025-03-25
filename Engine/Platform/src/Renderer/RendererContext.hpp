#pragma once

#include <core.hpp>

namespace Engine {
class RendererContext
{
public:
    virtual ~RendererContext() = default;

    virtual void SwapBuffers() = 0;

    static std::unique_ptr<RendererContext> Create(void* windowHandle);

protected:
    RendererContext(void* windowHandle) : m_WindowHandle(windowHandle) {}

protected:
    void* m_WindowHandle;
};
} // namespace Engine