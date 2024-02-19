#pragma once

#include "Buffer.h"
#include <span>

namespace gp {
    class GPAPI IndexBuffer final : public Buffer {
    public:
        IndexBuffer();

        IndexBuffer(const uint32_t *indices, int32_t length);

        IndexBuffer(std::span<uint32_t> indices);

        IndexBuffer(std::initializer_list<uint32_t> indices);

        IndexBuffer(const IndexBuffer &) = delete;

        IndexBuffer(IndexBuffer &&other) noexcept = default;

        void setData(const void *data, int32_t length) override;

    protected:
        uint32_t _getBufferTarget() const override;

        uint32_t _getBufferUsage() const override;

        std::string _getClassString() const override;
    };
}
