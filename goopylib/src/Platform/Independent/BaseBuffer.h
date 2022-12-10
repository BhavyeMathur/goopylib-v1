#pragma once

#include "pch.h"

// Buffer Layout
namespace gp {
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    #if GP_USING_OPENGL
    GLenum shaderOpenGLType(ShaderDataType type);
    #endif

    int shaderTypeSize(ShaderDataType type);

    class BufferElement {
    public:
        BufferElement(ShaderDataType type, std::string name, bool normalized = false);

        int getCount() const;

        ShaderDataType getType() const;

        bool isNormalized() const;

        int m_Size;
        size_t m_Offset;

    private:
        std::string m_Name;
        ShaderDataType m_Type;
        bool m_Normalized;
    };

    class BufferLayout {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements);

        int getStride() const;

        const std::vector<BufferElement> &getElements() const;

        std::vector<BufferElement>::iterator begin();

        std::vector<BufferElement>::iterator end();

        std::vector<BufferElement>::const_iterator begin() const;

        std::vector<BufferElement>::const_iterator end() const;

    private:
        void calculateOffsetAndStride();

    private:
        std::vector<BufferElement> m_Elements;
        int m_Stride{};
    };
}

// Generic Buffer
namespace gp {
    class BaseBuffer {
    public:
        explicit BaseBuffer(int count) : m_Count(count) {};

        virtual ~BaseBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        int count() const {
            return m_Count;
        };

    private:
        int m_Count;
    };
}

// Vertex Buffer
namespace gp {
    class BaseVertexBuffer : public BaseBuffer {
    public:
        BaseVertexBuffer(float *indices, int count)
                : BaseBuffer(count) {};

        const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

        virtual void setData(const void *data, uint32_t size) = 0;

    private:
        BufferLayout m_Layout{};
    };
}

// Index Buffer
namespace gp {
    class BaseIndexBuffer : public BaseBuffer {
    public:
        BaseIndexBuffer(uint32_t *indices, int count)
        : BaseBuffer(count) {};
    };
}
