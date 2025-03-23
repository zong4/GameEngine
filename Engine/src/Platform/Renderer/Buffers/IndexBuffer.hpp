#pragma once

#include "Buffer.hpp"

namespace Engine
{
class IndexBuffer : public Buffer
{
  public:
    virtual ~IndexBuffer() = default;

    static std::unique_ptr<IndexBuffer> Create(std::span<const uint32_t> indices, BufferUsage usage = BufferUsage::Static);

  public:
    uint32_t GetSize() const { return m_Size; }

  protected:
    IndexBuffer() = default;

  protected:
    uint32_t m_Size = 0;
};
} // namespace Engine