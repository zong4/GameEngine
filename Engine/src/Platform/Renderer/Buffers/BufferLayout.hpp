#pragma once

#include "Buffer.hpp"

namespace Engine
{
class BufferElement
{
  public:
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

  public:
    std::string    GetName() const { return m_Name; }
    ShaderDataType GetType() const { return m_Type; }
    uint32_t       GetOffset() const { return m_Offset; }
    bool           GetNormalized() const { return m_Normalized; }
    uint32_t       GetComponentCount() const;
    void           SetOffset(uint32_t offset) { m_Offset = offset; }

  private:
    std::string    m_Name;
    ShaderDataType m_Type;
    uint32_t       m_Offset;
    bool           m_Normalized;
};

class BufferLayout
{
  public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) { CalculateOffsetsAndStride(); }

  public:
    std::vector<BufferElement>::iterator       begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator       end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    uint32_t                          GetStride() const { return m_Stride; }

  private:
    void CalculateOffsetsAndStride();

  private:
    std::vector<BufferElement> m_Elements;
    uint32_t                   m_Stride = 0;
};
} // namespace Engine