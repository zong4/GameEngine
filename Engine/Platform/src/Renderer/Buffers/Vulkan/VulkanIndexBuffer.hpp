#pragma once

#include "../IndexBuffer.hpp"
#include <vulkan/vulkan.h>

namespace Engine {
class VulkanIndexBuffer final : public IndexBuffer
{
public:
    explicit VulkanIndexBuffer(uint32_t size);
    explicit VulkanIndexBuffer(std::span<uint32_t> indices);
    ~VulkanIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

public:
    virtual void SetData(std::span<uint32_t> indices, uint32_t offset = 0) override;
};
} // namespace Engine