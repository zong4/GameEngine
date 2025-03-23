#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class RendererContext
{
  public:
    virtual ~RendererContext() = default;

    virtual void SwapBuffers() = 0;

    static std::unique_ptr<RendererContext> Create(void* window);

  protected:
    RendererContext() = default;
};
} // namespace Engine