#pragma once

#include "src/pch.h"
#include "src/goopylib/Core/BufferLayout.h"

// Generic Buffer
namespace gp {
    class Buffer {
    public:
        virtual ~Buffer() = default;

        uint32_t count() const;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

    protected:
        uint32_t m_Count = 0;
        uint32_t m_RendererID = 0;

        explicit Buffer() = default;

        explicit Buffer(uint32_t count);

    };
}

// Index Buffer
namespace gp {
    class BaseIndexBuffer : public Buffer {

        friend class Renderer;

    public:
        ~BaseIndexBuffer() override;

        void bind() const override = 0;

        void unbind() const override = 0;

    protected:
        explicit BaseIndexBuffer(uint32_t count);
    };
}
