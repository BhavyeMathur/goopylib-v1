#pragma once

#include "src/pch.h"
#include "src/goopylib/Core/BufferLayout.h"

// Generic Buffer
namespace gp {
    class BaseBuffer {
    public:
        BaseBuffer() = default;

        explicit BaseBuffer(int32_t count);

        virtual ~BaseBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        int32_t count() const;

    protected:
        int32_t m_Count = 0;
    };
}

// Vertex Buffer
namespace gp {
    class BaseVertexBuffer : public BaseBuffer {
    public:
        explicit BaseVertexBuffer(int32_t count = 0);

        ~BaseVertexBuffer() override;

        void bind() const override = 0;

        void unbind() const override = 0;

        const BufferLayout &getLayout() const;

        void setLayout(const BufferLayout &layout);

        virtual void setData(const float *data, int32_t count) = 0;

    private:
        BufferLayout m_Layout;
    };
}

// Index Buffer
namespace gp {
    class BaseIndexBuffer : public BaseBuffer {
    public:
        explicit BaseIndexBuffer(int32_t count);

        ~BaseIndexBuffer() override;

        void bind() const override = 0;

        void unbind() const override = 0;
    };
}
