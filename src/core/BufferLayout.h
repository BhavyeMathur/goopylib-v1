#pragma once

#include "gp.h"
#include <vector>
#include <memory>


// Buffer Layout Data Types
namespace gp {
    enum class GPAPI ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    [[nodiscard]] GPAPI int32_t shaderTypeSize(ShaderDataType type);
}

// Buffer Layout Element
namespace gp {
    class GPAPI BufferElement {
        friend class BufferLayout;

    public:
        BufferElement(ShaderDataType type, const char *name, bool normalized = false);

        [[nodiscard]] int32_t getCount() const;

        [[nodiscard]] ShaderDataType getDataType() const;

        [[nodiscard]] bool isNormalised() const;

        [[nodiscard]] size_t getOffset() const;

        [[nodiscard]] const char *getName() const;

    private:
        const char *m_Name;
        ShaderDataType m_Type;
        bool m_Normalized;

        int32_t m_Size = 0;
        size_t m_Offset = 0;
    };
}

// Buffer Layout
namespace gp {
    class GPAPI BufferLayout {
        friend class VertexArray;

        friend class Buffer;

    public:
        BufferLayout(BufferElement *elements, int32_t count);

        BufferLayout(std::initializer_list<BufferElement> elements);

        [[nodiscard]] std::vector<BufferElement>::iterator begin();

        [[nodiscard]] std::vector<BufferElement>::iterator end();

        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const;

        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const;

        void calculateOffsetAndStride();

    private:
        std::vector<BufferElement> m_Elements;
        int32_t m_Stride = 0;
        uint32_t m_Count = 0;
    };
}
