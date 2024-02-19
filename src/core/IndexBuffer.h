#pragma once

#include "Buffer.h"

namespace gp {
    class GPAPI IndexBuffer final : public Buffer {

    public:
        IndexBuffer(const int32_t *indices = nullptr, int32_t length = 0);

        IndexBuffer(std::span<int32_t> indices);

        IndexBuffer(std::initializer_list<int32_t> indices);

        IndexBuffer(const IndexBuffer &) = delete;

        IndexBuffer(IndexBuffer &&other) noexcept = default;

        void setData(const void *data, int32_t length) override;

    protected:
        uint32_t _getBufferTarget() const override;
    };
}
