#pragma once

#include "Buffer.h"

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
