#pragma once

#include "gp.h"
#include "BufferLayout.h"

// Generic Buffer
namespace gp {
    class Buffer {
    public:
        GPAPI Buffer(uint32_t count, const BufferLayout &layout = {});

        GPAPI Buffer(const Buffer &) = delete;

        GPAPI Buffer(Buffer &&other) noexcept;

        GPAPI ~Buffer() noexcept;

        GPAPI void init();

        GPAPI void bind() const;

        [[nodiscard]] GPAPI uint32_t count() const;

        GPAPI void setData(const void *data, uint32_t count);

        GPAPI void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] GPAPI const BufferLayout &getLayout() const;

    protected:
        uint32_t m_Count = 0;
        uint32_t m_RendererID = 0;

        BufferLayout m_Layout;

        GPAPI virtual uint32_t _getBufferTarget() const = 0;
    };
}

// Vertex Buffer
namespace gp {
    class VertexBuffer final : public Buffer {

        friend class VertexArray;

    public:
        GPAPI VertexBuffer(const VertexBuffer &) = delete;

        GPAPI VertexBuffer(VertexBuffer &&other) noexcept = default;

        GPAPI static void unbind();

    protected:
        GPAPI uint32_t _getBufferTarget() const override;

    private:
        GPAPI VertexBuffer(const BufferLayout &layout);
    };
}

// Index Buffer
namespace gp {
    class IndexBuffer final : public Buffer {

    public:
        GPAPI IndexBuffer(uint32_t count, uint32_t *indices);

        GPAPI IndexBuffer(std::initializer_list<uint32_t> indices);

        GPAPI IndexBuffer(const IndexBuffer &) = delete;

        GPAPI IndexBuffer(IndexBuffer &&other) noexcept = default;

        GPAPI static void unbind();

    protected:
        GPAPI uint32_t _getBufferTarget() const override;
    };
}

// Uniform Buffer
namespace gp {
    class UniformBuffer final : public Buffer {

    public:
        GPAPI UniformBuffer(const BufferLayout &layout);

        GPAPI UniformBuffer(UniformBuffer &&other) noexcept = default;

        GPAPI UniformBuffer(const UniformBuffer &) = delete;

        GPAPI static void unbind();

        GPAPI void setBinding(uint32_t binding) const;

    protected:
        GPAPI uint32_t _getBufferTarget() const override;
    };
}
