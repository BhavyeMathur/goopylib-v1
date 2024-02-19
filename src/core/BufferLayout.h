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

        [[nodiscard]] const char *getName() const;

        [[nodiscard]] ShaderDataType getDataType() const;

        [[nodiscard]] int32_t getCount() const;

        [[nodiscard]] int32_t getSize() const;

        [[nodiscard]] int32_t getOffset() const;

        [[nodiscard]] bool isNormalized() const;

    private:
        const char *m_Name;
        ShaderDataType m_Type;

        int32_t m_Size = 0;
        int32_t m_Offset = 0;
        bool m_Normalized;
    };
}

// Buffer Layout
namespace gp {
    class GPAPI BufferLayout {
    public:
        BufferLayout(const BufferElement *elements, int32_t count);

        BufferLayout(std::initializer_list<BufferElement> elements);

        int32_t getStride() const;

        int32_t getCount() const;

        [[nodiscard]] std::vector<BufferElement>::iterator begin();

        [[nodiscard]] std::vector<BufferElement>::iterator end();

        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const;

        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const;

    private:
        int32_t m_Stride = 0;
        int32_t m_Count = 0;

        std::vector<BufferElement> m_Elements;

        void _calculateOffsetAndStride();
    };
}
