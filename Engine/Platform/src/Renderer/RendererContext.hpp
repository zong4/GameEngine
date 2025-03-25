#pragma once

#include <core.hpp>

namespace Engine {
class RendererContext
{
public:
    virtual ~RendererContext() = default;

    virtual void SwapBuffers() = 0;

    static std::shared_ptr<Engine::RendererContext> Create(void* windowHandle);
    static std::shared_ptr<RendererContext> Get() { return s_Instance.lock(); }

protected:
    RendererContext(void* windowHandle) : m_WindowHandle(windowHandle) {}

protected:
    static std::weak_ptr<RendererContext> s_Instance;
    void* m_WindowHandle;
};
} // namespace Engine