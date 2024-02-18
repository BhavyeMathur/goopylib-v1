#pragma once

#include "Buffer.h"

namespace gp {
    class IndexBuffer final : public Buffer {

    public:
        IndexBuffer(const uint32_t *indices, int32_t length);

        IndexBuffer(std::initializer_list<uint32_t> indices);

        IndexBuffer(const IndexBuffer &) = delete;

        IndexBuffer(IndexBuffer &&other) noexcept = default;

        void setData(const void *data, int32_t length) override;

        static void unbind();

    protected:
        uint32_t _getBufferTarget() const override;
    };
}
