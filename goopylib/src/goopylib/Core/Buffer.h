#pragma once

#include "src/Platform/Independent/Buffer.h"

// TODO Vertex Buffer with non-float data

// Vertex Buffer
namespace gp {
    class VertexBuffer final : public Buffer {

        friend class Renderer;

    public:
        ~VertexBuffer() override;

        void bind() const override;

        void unbind() const override;

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
    class IndexBuffer final : public BaseIndexBuffer {

        friend class Renderer;

    public:
        ~IndexBuffer() override;

        void bind() const override;

        void unbind() const override;

    private:
        uint32_t m_RendererID = 0;

        IndexBuffer(uint32_t count, uint32_t *indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);
    };
}
