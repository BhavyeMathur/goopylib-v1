#pragma once

#include "Buffer.h"

namespace gp {
    class GPAPI UniformBuffer final : public Buffer {

    public:
        UniformBuffer(const BufferLayout &layout);

        UniformBuffer(UniformBuffer &&other) noexcept = default;

        UniformBuffer(const UniformBuffer &) = delete;

        void setBinding(uint32_t binding) const;

    protected:
        uint32_t _getBufferTarget() const override;

        std::string _getClassString() const override;
    };
}
