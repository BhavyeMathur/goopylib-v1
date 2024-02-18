#pragma once

#include "Buffer.h"

namespace gp {
    class GPAPI VertexBuffer final : public Buffer {

        friend class VertexArray;

    public:
        VertexBuffer(const VertexBuffer &) = delete;

        VertexBuffer(VertexBuffer &&other) noexcept = default;

        static void unbind();

    protected:
        uint32_t _getBufferTarget() const override;

    private:
        VertexBuffer(const BufferLayout &layout);
    };
}
