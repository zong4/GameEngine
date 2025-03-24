#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

  public:
    uint32_t GetCount() const { return m_Count; }
    void     SetCount(uint32_t count) { m_Count = count; }

  protected:
    IndexBuffer() = default;

  protected:
    uint32_t m_RendererID = 0;
    uint32_t m_Count      = 0;
};
} // namespace Engine