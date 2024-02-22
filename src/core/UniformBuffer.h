#pragma once

#include "Buffer.h"

namespace gp {
    /**
     * An object representing a Uniform Buffer to store uniforms
     */
    class GPAPI UniformBuffer final : public Buffer {

    public:
        /**
         * An object representing a Uniform Buffer to store uniforms
         *
         * @param layout the structure of buffer data
         */
        UniformBuffer(const BufferLayout &layout);

        UniformBuffer(UniformBuffer &&other) noexcept = default;

        UniformBuffer(const UniformBuffer &) = delete;

        /**
         * Binds the buffer to a Shader uniform source
         *
         * @param binding the index of the binding point in the Shader
         */
        void setBinding(uint32_t binding) const;

    protected:
        uint32_t _getBufferTarget() const override;

        std::string _getClassString() const override;
    };
}
