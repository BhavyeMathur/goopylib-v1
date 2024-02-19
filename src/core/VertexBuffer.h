#pragma once

#include "Buffer.h"

namespace gp {
    class GPAPI VertexBuffer final : public Buffer {

        friend class VertexArray;

    public:
        VertexBuffer(const BufferLayout &layout);

        VertexBuffer(const VertexBuffer &) = delete;

        VertexBuffer(VertexBuffer &&other) noexcept = default;

    protected:
        uint32_t _getBufferTarget() const override;

        std::string _getClassString() const override;
    };
}
