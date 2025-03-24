#pragma once

#include <core.hpp>

namespace Engine {
class IndexBuffer
{
public:
    IndexBuffer() = delete;
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static std::shared_ptr<IndexBuffer> Create(uint32_t size);
    static std::shared_ptr<IndexBuffer> Create(std::span<uint32_t> indices);

public:
    uint32_t GetSize() const { return m_Size; }
    void SetSize(uint32_t size) { m_Size = size; }
    virtual void SetData(std::span<uint32_t> indices, uint32_t offset = 0) = 0;

protected:
    IndexBuffer(uint32_t size) : m_Size(size) {}

protected:
    uint32_t m_RendererID = 0;
    uint32_t m_Size = 0;
};
} // namespace Engine