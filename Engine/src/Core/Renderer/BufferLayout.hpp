#pragma once

namespace Engine
{
enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    case ShaderDataType::None:
        return 0;
    }

    ENGINE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

class BufferElement
{
  public:
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : m_Name(name), m_Type(type), m_Size(0), m_Offset(0), m_Normalized(normalized)
    {
    }

  public:
    inline std::string    GetName() const { return m_Name; }
    inline ShaderDataType GetType() const { return m_Type; }
    inline uint32_t       GetSize() const { return m_Size; }
    inline uint32_t       GetOffset() const { return m_Offset; }
    inline bool           GetNormalized() const { return m_Normalized; }
    uint32_t              GetComponentCount() const;
    inline void           SetOffset(uint32_t offset) { m_Offset = offset; }

  private:
    std::string    m_Name;
    ShaderDataType m_Type;
    uint32_t       m_Size;
    uint32_t       m_Offset;
    bool           m_Normalized;
};

class BufferLayout
{
  public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

  public:
    inline const std::vector<BufferElement>&   GetElements() const { return m_Elements; }
    inline uint32_t                            GetStride() const { return m_Stride; }
    std::vector<BufferElement>::iterator       begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator       end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

  private:
    void CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_Stride        = 0;
        for (auto& element : m_Elements) {
            element.SetOffset(offset);
            offset += ShaderDataTypeSize(element.GetType());
            m_Stride += offset;
        }
    }

  private:
    std::vector<BufferElement> m_Elements;
    uint32_t                   m_Stride = 0;
};
} // namespace Engine