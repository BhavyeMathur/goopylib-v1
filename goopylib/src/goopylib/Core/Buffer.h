#pragma once

#include "src/Platform/Independent/BaseBuffer.h"

// TODO Vertex Buffer with non-float data

// Vertex Buffer
namespace gp {
    class GPAPI VertexBuffer final : public BaseVertexBuffer {
    public:
        ~VertexBuffer() override;

        void bind() const override;

        void unbind() const override;

        void setData(const void *data, uint32_t count) override;

        void setData(const void *data, uint32_t count, uint32_t offset) override;

        // Static Methods

        static Ref<VertexBuffer> create(int32_t count = 0, float *vertices = nullptr) {
            return Ref<VertexBuffer>(new VertexBuffer(count, vertices));
        }

        static Ref<VertexBuffer> create(std::initializer_list<float> vertices) {
            return Ref<VertexBuffer>(new VertexBuffer(vertices));
        }

    private:
        uint32_t m_RendererID = 0;

        explicit VertexBuffer(uint32_t count = 0, void *vertices = nullptr);

        VertexBuffer(std::initializer_list<float> vertices);
    };
}

// Index Buffer
namespace gp {
    class GPAPI IndexBuffer final : public BaseIndexBuffer {
    public:
        ~IndexBuffer() override;

        void bind() const override;

        void unbind() const override;

        // Static Methods

        static Ref<IndexBuffer> create(int32_t count, uint32_t *indices) {
            return Ref<IndexBuffer>(new IndexBuffer(count, indices));
        }

        static Ref<IndexBuffer> create(std::initializer_list<uint32_t> indices) {
            return Ref<IndexBuffer>(new IndexBuffer(indices));
        }

    private:
        uint32_t m_RendererID = 0;

        IndexBuffer(uint32_t count, uint32_t *indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);
    };
}
