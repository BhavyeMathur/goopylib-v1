#pragma once

#include "Buffer.h"

namespace gp {
    /**
     * An object representing an Index Buffer
     */
    class GPAPI IndexBuffer final : public Buffer {
    public:
        /**
         * An object representing an Index Buffer
         */
        IndexBuffer();

        /**
         * An object representing an Index Buffer
         *
         * @param indices pointer to an array of indices
         * @param length number of indices
         *
         * @throws std::invalid_argument: if length == 0 and indices is nullptr
         * @throws std::invalid_argument: if length is negative
         */
        IndexBuffer(const int32_t *indices, int32_t length);

        /**
         * An object representing an Index Buffer
         *
         * @param indices sequence of indices
         */
        IndexBuffer(std::span<int32_t> indices);

        /**
         * An object representing an Index Buffer
         *
         * @param indices sequence of indices
         */
        IndexBuffer(std::initializer_list<int32_t> indices);

        IndexBuffer(const IndexBuffer &) = delete;

        IndexBuffer(IndexBuffer &&other) noexcept = default;

    protected:
        uint32_t _getBufferTarget() const override;

        uint32_t _getBufferUsage() const override;

        std::string _getClassString() const override;
    };
}
