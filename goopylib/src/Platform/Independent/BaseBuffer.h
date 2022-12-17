#pragma once

#include "pch.h"

// Buffer Layout
namespace gp {
    enum class GPAPI ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    #if GP_USING_OPENGL

    GLenum shaderOpenGLType(ShaderDataType type);

    #endif

    int32_t shaderTypeSize(ShaderDataType type);

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
        void calculateOffsetAndStride();

    private:
        std::vector<BufferElement> m_Elements;
        int32_t m_Stride = 0;
    };
}

// Generic Buffer
namespace gp {
    class BaseBuffer {
    public:
        BaseBuffer() = default;

        explicit BaseBuffer(int32_t count) : m_Count(count) {
        };

        virtual ~BaseBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        int32_t count() const {
            return m_Count;
        };

    private:
        int32_t m_Count = 0;
    };
}

// Vertex Buffer
namespace gp {
    class BaseVertexBuffer : public BaseBuffer {
    public:
        BaseVertexBuffer();

        explicit BaseVertexBuffer(int32_t count);

        ~BaseVertexBuffer() override;

        const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

        virtual void setData(const void *data, int32_t count) = 0;

    private:
        BufferLayout m_Layout;
    };
}

// Index Buffer
namespace gp {
    class BaseIndexBuffer : public BaseBuffer {
    public:
        explicit BaseIndexBuffer(int32_t count);

        ~BaseIndexBuffer() override;
    };
}
