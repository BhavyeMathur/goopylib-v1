#pragma once

#include <utility>

#include "Platform/Independent/BaseBuffer.h"

// Vertex Buffer
namespace gp {
    class GPAPI VertexBuffer final : public BaseVertexBuffer {
    public:
        VertexBuffer(float *vertices, int count);

        ~VertexBuffer() override;

        void bind() const override;

        void unbind() const override;

        void setData(const void *data, uint32_t size) override;

        static std::shared_ptr<BaseVertexBuffer> create(float *vertices, int count);

    private:
        uint32_t m_RendererID{};
    };
}

// Index Buffer
namespace gp {
    class GPAPI IndexBuffer final : public BaseIndexBuffer {
    public:
        IndexBuffer(uint32_t *indices, int count);

        ~IndexBuffer() override;

        void bind() const override;

        void unbind() const override;

        static std::shared_ptr<BaseIndexBuffer> create(uint32_t *vertices, int count);

    private:
        uint32_t m_RendererID{};
    };
}
