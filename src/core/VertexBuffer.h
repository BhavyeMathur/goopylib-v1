#pragma once

#include "Buffer.h"

namespace gp {
    /**
     * An object representing a Vertex Buffer to store vertex data
     */
    class GPAPI VertexBuffer final : public Buffer {

    public:
        /**
         * An object representing a Vertex Buffer to store vertex data
         *
         * @param layout the structure of vertex data
         */
        VertexBuffer(const BufferLayout &layout);

        VertexBuffer(const VertexBuffer &) = delete;

        VertexBuffer(VertexBuffer &&other) noexcept = default;

    protected:
        uint32_t _getBufferTarget() const override;

        std::string _getClassString() const override;
    };
}
