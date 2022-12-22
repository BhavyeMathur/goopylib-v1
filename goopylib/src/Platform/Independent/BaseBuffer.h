#pragma once

#include "src/pch.h"
#include "src/goopylib/Core/BufferLayout.h"

// Generic Buffer
namespace gp {
    class BaseBuffer {
    public:
        virtual ~BaseBuffer() = default;

        uint32_t count() const;

    protected:
        uint32_t m_Count = 0;

        BaseBuffer() = default;

        explicit BaseBuffer(uint32_t count);

    private:
        virtual void bind() const = 0;

        virtual void unbind() const = 0;
    };
}

// Vertex Buffer
namespace gp {
    class BaseVertexBuffer : public BaseBuffer {
    public:
        ~BaseVertexBuffer() override;

        const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

        virtual void setData(const void *data, uint32_t count) = 0;

        virtual void setData(const void *data, uint32_t count, uint32_t offset) = 0;

    protected:
        BufferLayout m_Layout;

        explicit BaseVertexBuffer(uint32_t count = 0);

    private:
        void bind() const override = 0;

        void unbind() const override = 0;
    };
}

// Index Buffer
namespace gp {
    class BaseIndexBuffer : public BaseBuffer {
    public:
        ~BaseIndexBuffer() override;

    protected:
        explicit BaseIndexBuffer(uint32_t count);

    private:
        void bind() const override = 0;

        void unbind() const override = 0;
    };
}
