#pragma once

#include "src/Platform/Independent/BaseBuffer.h"

// TODO Vertex Buffer with non-float data

// Vertex Buffer
namespace gp {
    class GPAPI VertexBuffer final : public BaseVertexBuffer {
    public:
        explicit VertexBuffer(int32_t count = 0, float *vertices = nullptr);

        VertexBuffer(std::initializer_list<float> vertices);

        ~VertexBuffer() override;

        void bind() const override;

        void unbind() const override;

        void setData(const float *data, int32_t count) override;

        // Static Methods

        static Ref<VertexBuffer> create(int32_t count = 0, float *vertices = nullptr) {
            return CreateRef<VertexBuffer>(count, vertices);
        }

        static Ref<VertexBuffer> create(std::initializer_list<float> vertices) {
            return CreateRef<VertexBuffer>(vertices);
        }

    private:
        uint32_t m_RendererID = 0;
    };
}

// Index Buffer
namespace gp {
    class GPAPI IndexBuffer final : public BaseIndexBuffer {
    public:
        IndexBuffer(int32_t count, uint32_t *indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);

        ~IndexBuffer() override;

        void bind() const override;

        void unbind() const override;

        // Static Methods

        static Ref<IndexBuffer> create(int32_t count, uint32_t *indices) {
            return CreateRef<IndexBuffer>(count, indices);
        }

        static Ref<IndexBuffer> create(std::initializer_list<uint32_t> indices) {
            return CreateRef<IndexBuffer>(indices);
        }

    private:
        uint32_t m_RendererID = 0;
    };
}
