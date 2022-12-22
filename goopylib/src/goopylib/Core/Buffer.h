#pragma once

#include "pch.h"
#include "BufferLayout.h"

// TODO Vertex Buffer with non-float data

// Generic Buffer
namespace gp {
    class Buffer {
    public:
        virtual ~Buffer() = default;

        uint32_t count() const;

    protected:
        uint32_t m_Count = 0;
        uint32_t m_RendererID = 0;

        explicit Buffer() = default;

        explicit Buffer(uint32_t count);
    };
}

// Vertex Buffer
namespace gp {
    class VertexBuffer final : public Buffer {

        friend class Renderer;

    public:
        ~VertexBuffer() override;

        void bind() const;

        static void unbind();

        void setData(const void *data, uint32_t count);

        void setData(const void *data, uint32_t count, uint32_t offset) const;

        const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

    private:
        BufferLayout m_Layout{};

        explicit VertexBuffer(uint32_t count = 0, void *vertices = nullptr);

        VertexBuffer(std::initializer_list<float> vertices);
    };
}

// Index Buffer
namespace gp {
    class IndexBuffer final : public Buffer {

        friend class Renderer;

    public:
        ~IndexBuffer() override;

        void bind() const;

        static void unbind();

    private:
        IndexBuffer(uint32_t count, uint32_t *indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);
    };
}
