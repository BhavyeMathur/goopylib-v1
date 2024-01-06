#pragma once

#include "gp.h"
#include "BufferLayout.h"

// Generic Buffer
namespace gp {
    class Buffer {
    public:
        virtual ~Buffer() = default;

        [[nodiscard]] uint32_t count() const;

    protected:
        uint32_t m_Count = 0;
        uint32_t m_RendererID = 0;

        GPAPI Buffer() = default;

        GPAPI Buffer(uint32_t count);
    };
}

// Vertex Buffer
namespace gp {
    class VertexBuffer : public Buffer {

        friend class Renderer;

    public:
        GPAPI VertexBuffer(uint32_t count = 0, void *vertices = nullptr);

        GPAPI ~VertexBuffer() override;

        GPAPI void bind() const;

        GPAPI static void unbind();

        GPAPI void setData(const void *data, uint32_t count);

        GPAPI void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] GPAPI const BufferLayout &getLayout() const;

        GPAPI void setLayout(const BufferLayout &layout);

    private:
        BufferLayout m_Layout{};
    };
}

// Index Buffer
namespace gp {
    class IndexBuffer final : public Buffer {

        friend class VertexArray;

    public:
        GPAPI IndexBuffer(uint32_t count, uint32_t *indices);

        GPAPI IndexBuffer(std::initializer_list<uint32_t> indices);

        GPAPI ~IndexBuffer() override;

        GPAPI void bind() const;

        GPAPI static void unbind();
    };
}

// Uniform Buffer
namespace gp {
    class UniformBuffer final : public Buffer {

    public:
        GPAPI UniformBuffer(BufferLayout &&layout);

        GPAPI ~UniformBuffer() override;

        GPAPI void bind() const;

        GPAPI static void unbind();

        GPAPI void setData(const void *data, uint32_t count);

        GPAPI void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] GPAPI const BufferLayout &getLayout() const;

        GPAPI void setBinding(uint32_t binding) const;

    private:
        BufferLayout m_Layout;
    };
}
