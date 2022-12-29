#pragma once

#include "gp.h"
#include <vector>
#include <memory>

#if GP_USING_OPENGL

#include <OpenGL/gl.h>

#endif


// Buffer Layout Data Types
namespace gp {
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    #if GP_USING_OPENGL

    GLenum shaderOpenGLType(ShaderDataType type);

    #endif

    int32_t shaderTypeSize(ShaderDataType type);
}

// Buffer Layout Element
namespace gp {
    class BufferElement {

        friend class BufferLayout;
        friend class VertexArray;

    public:
        BufferElement(ShaderDataType type, const char *name, bool normalized = false);

        [[nodiscard]] int32_t getCount() const;

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
    class BufferLayout {

        friend class VertexArray;
        friend class VertexBuffer;
        friend class UniformBuffer;

    public:
        BufferLayout(BufferElement *elements, int32_t count);

        BufferLayout(std::initializer_list<BufferElement> elements);

    private:
        std::vector<BufferElement>::iterator begin();

        std::vector<BufferElement>::iterator end();

        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const;

        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const;

    private:
        std::vector<BufferElement> m_Elements;
        int32_t m_Stride = 0;
        uint32_t m_Count = 0;

        void calculateOffsetAndStride();
    };
}
