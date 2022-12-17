#pragma once

#include "src/pch.h"


// Buffer Layout Data Types
namespace gp {
    enum class GPAPI ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    #if GP_USING_OPENGL

    GLenum shaderOpenGLType(ShaderDataType type);

    #endif

    int32_t shaderTypeSize(ShaderDataType type);
}

// Buffer Layout Element
namespace gp {
    class GPAPI BufferElement {
    public:
        BufferElement(ShaderDataType type, const char *name, bool normalized = false);

        const char *getName() const;

        int32_t getCount() const;

        ShaderDataType getType() const;

        bool isNormalized() const;

        int32_t m_Size = 0;
        size_t m_Offset = 0;

    private:
        const char *m_Name;
        ShaderDataType m_Type;
        bool m_Normalized;
    };
}

// Buffer Layout
namespace gp {
    class GPAPI BufferLayout {
    public:
        BufferLayout(BufferElement *elements, int32_t count);

        BufferLayout(std::initializer_list<BufferElement> elements);

        int32_t getStride() const;

        const std::vector<BufferElement> &getElements() const;

        std::vector<BufferElement>::iterator begin();

        std::vector<BufferElement>::iterator end();

        std::vector<BufferElement>::const_iterator begin() const;

        std::vector<BufferElement>::const_iterator end() const;

    private:
        std::vector<BufferElement> m_Elements;
        int32_t m_Stride = 0;

        void calculateOffsetAndStride();
    };
}
