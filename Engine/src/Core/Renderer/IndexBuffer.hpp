#pragma once

#include "EnginePCH.hpp"

namespace Engine
{
class IndexBuffer
{
  public:
    IndexBuffer()          = default;
    virtual ~IndexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

  public:
    inline uint32_t GetCount() const { return m_Count; }
    inline void     SetCount(uint32_t count) { m_Count = count; }

  protected:
    uint32_t m_RendererID;
    uint32_t m_Count;
};
} // namespace Engine