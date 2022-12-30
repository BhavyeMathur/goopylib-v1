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

        Buffer() = default;

        Buffer(uint32_t count);
    };
}

// Vertex Buffer
namespace gp {
    class VertexBuffer : public Buffer {

        friend class Renderer;

    public:
        ~VertexBuffer() override;

        void bind() const;

        static void unbind();

        void setData(const void *data, uint32_t count);

        void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

    protected:
        VertexBuffer(uint32_t count = 0, void *vertices = nullptr);

    private:
        BufferLayout m_Layout{};
    };
}

// Index Buffer
namespace gp {
    class IndexBuffer final : public Buffer {

        friend class VertexArray;

    public:
        ~IndexBuffer() override;

        void bind() const;

        static void unbind();

    private:
        IndexBuffer(uint32_t count, uint32_t *indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);
    };
}

// Uniform Buffer
namespace gp {
    class UniformBuffer final : public Buffer {

        friend class Renderer;

    public:
        ~UniformBuffer() override;

        void bind() const;

        static void unbind();

        void setData(const void *data, uint32_t count);

        void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] const BufferLayout &getLayout() const;

        void setBinding(uint32_t binding) const;

    private:
        UniformBuffer(BufferLayout &&layout);

        BufferLayout m_Layout;
    };
}
