#pragma once

#include "Buffer.h"

namespace gp {
    class UniformBuffer final : public Buffer {

    public:
        GPAPI UniformBuffer(const BufferLayout &layout);

        GPAPI UniformBuffer(UniformBuffer &&other) noexcept = default;

        GPAPI UniformBuffer(const UniformBuffer &) = delete;

        GPAPI static void unbind();

        GPAPI void setBinding(uint32_t binding) const;

    protected:
        GPAPI uint32_t _getBufferTarget() const override;
    };
}
