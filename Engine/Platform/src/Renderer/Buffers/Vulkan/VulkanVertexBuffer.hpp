#pragma once

#include "../VertexBuffer.hpp"
#include <vulkan/vulkan.h>

namespace Engine {
class VulkanVertexBuffer final : public VertexBuffer
{
public:
    explicit VulkanVertexBuffer(uint32_t size);
    explicit VulkanVertexBuffer(std::span<const float> vertices, BufferLayout layout);
    explicit VulkanVertexBuffer(std::span<const double> vertices, BufferLayout layout);
    ~VulkanVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

public:
    virtual void SetData(std::span<const float> vertices, uint32_t offset = 0) override;
    virtual void SetData(std::span<const double> vertices, uint32_t offset = 0) override;
};
} // namespace Engine