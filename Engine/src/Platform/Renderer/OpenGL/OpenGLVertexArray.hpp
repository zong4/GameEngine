#pragma once

#include "Platform/Renderer/VertexArray.hpp"

namespace Engine
{
class OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

  public:
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
    virtual const std::shared_ptr<IndexBuffer>&               GetIndexBuffer() const override;
    virtual void                                              AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void                                              SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

  private:
    uint32_t                                   m_VertexBufferIndex = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer>               m_IndexBuffer;
};
} // namespace Engine