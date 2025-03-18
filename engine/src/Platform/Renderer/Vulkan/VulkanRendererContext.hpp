#pragma once

#include "Platform/Renderer/RendererContext.hpp"

namespace Engine
{
class VulkanRendererContext : public RendererContext
{
  public:
    VulkanRendererContext()          = default;
    virtual ~VulkanRendererContext() = default;

    virtual void Init() override;
    virtual void SwapBuffers() override;
};
} // namespace Engine