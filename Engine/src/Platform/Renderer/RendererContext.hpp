#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class RendererContext
{
  public:
    RendererContext()          = default;
    virtual ~RendererContext() = default;

    virtual void Init()        = 0;
    virtual void SwapBuffers() = 0;

    static std::unique_ptr<RendererContext> Create(void* window);
};
} // namespace Engine