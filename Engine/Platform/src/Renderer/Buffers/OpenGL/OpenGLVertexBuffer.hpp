#pragma once

#include "../VertexBuffer.hpp"
#include <glad/glad.h>

namespace Engine
{
class OpenGLVertexBuffer final : public VertexBuffer
{
public:
    explicit OpenGLVertexBuffer(uint32_t size);
    explicit OpenGLVertexBuffer(std::span<const float> vertices,
                                BufferLayout layout);
    explicit OpenGLVertexBuffer(std::span<const double> vertices,
                                BufferLayout layout);
    ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

public:
    virtual void SetData(std::span<const float> vertices,
                         uint32_t offset = 0) override;
    virtual void SetData(std::span<const double> vertices,
                         uint32_t offset = 0) override;
};
} // namespace Engine