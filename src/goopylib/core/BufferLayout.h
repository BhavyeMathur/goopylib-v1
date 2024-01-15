#pragma once

#include "gp.h"
#include <vector>
#include <memory>

#if GP_USING_OPENGL

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#endif


// Buffer Layout Data Types
namespace gp {
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    #if GP_USING_OPENGL

    [[nodiscard]] GLenum shaderOpenGLType(ShaderDataType type);

    #endif

    [[nodiscard]] int32_t shaderTypeSize(ShaderDataType type);
}

// Buffer Layout Element
namespace gp {
    class BufferElement {

        friend class BufferLayout;

    public:
        GPAPI BufferElement(ShaderDataType type, const char *name, bool normalized = false);

        [[nodiscard]] GPAPI int32_t getCount() const;

        [[nodiscard]] GPAPI ShaderDataType getDataType() const;

        [[nodiscard]] GPAPI bool isNormalised() const;

        [[nodiscard]] GPAPI size_t getOffset() const;

        [[nodiscard]] GPAPI const char *getName() const;

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

        friend class Buffer;

    public:
        GPAPI BufferLayout(BufferElement *elements, int32_t count);

        GPAPI BufferLayout(std::initializer_list<BufferElement> elements);

        [[nodiscard]] GPAPI std::vector<BufferElement>::iterator begin();

        [[nodiscard]] GPAPI std::vector<BufferElement>::iterator end();

        [[nodiscard]] GPAPI std::vector<BufferElement>::const_iterator begin() const;

        [[nodiscard]] GPAPI std::vector<BufferElement>::const_iterator end() const;

        GPAPI void calculateOffsetAndStride();

    private:
        std::vector<BufferElement> m_Elements;
        int32_t m_Stride = 0;
        uint32_t m_Count = 0;
    };
}
