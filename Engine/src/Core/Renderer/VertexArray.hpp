#pragma once

#include "Core/Renderer/IndexBuffer.hpp"
#include "Core/Renderer/VertexBuffer.hpp"

namespace Engine
{
class VertexArray
{
  public:
    VertexArray()          = default;
    virtual ~VertexArray() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static std::shared_ptr<VertexArray> Create();

  public:
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const std::shared_ptr<IndexBuffer>&               GetIndexBuffer() const   = 0;
    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)    = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)       = 0;

  protected:
    uint32_t m_RendererID;
};
} // namespace Engine