#pragma once

#include "../RendererContext.hpp"
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

namespace Engine {
class BGFXRendererContext final : public RendererContext
{
public:
    explicit BGFXRendererContext(void* windowHandle, bool vsync);
    virtual ~BGFXRendererContext();
    BGFXRendererContext(const BGFXRendererContext&) = delete;
    BGFXRendererContext& operator=(const BGFXRendererContext&) = delete;

    virtual void SwapBuffers() override;
};
} // namespace Engine