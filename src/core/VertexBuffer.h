#pragma once

#include "Buffer.h"

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
