#pragma once

#include "gp.h"
#include "BufferLayout.h"
#include <span>


namespace gp {
    /**
     * An object representing a buffer of data
     */
    class GPAPI Buffer {
    public:
        /**
         * An object representing a buffer of data
         *
         * @param length number of elements
         * @param layout structure of the data
         *
         * @throws std::invalid_argument: if length is negative
         */
        Buffer(int32_t length, const BufferLayout &layout);

        Buffer(const Buffer &) = delete;

        Buffer(Buffer &&other) noexcept;

        virtual ~Buffer() noexcept;

        /**
         * Initializes the data buffer
         * @throws std::runtime_error: if there is no active goopylib window
         */
        void init();

        /**
         * Binds the buffer as the currently active buffer
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void bind() const;

        /**
         * Unbinds any bound buffers
         *
         * @throws std::runtime_error: if there is no active goopylib window
         */
        void unbind() const;

        /**
         * @return the number of elements in the buffer
         */
        [[nodiscard]] int32_t length() const;

        /**
         * Sets the data in the buffer
         *
         * @param data pointer to a data array
         * @param length number of elements
         *
         * @throws std::invalid_argument: if length is negative
         * @throws std::invalid_argument: if length == 0 and indices is nullptr
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(const void *data, int32_t length);

        /**
         * Sets a subset of the data in the buffer
         *
         * @param data pointer to a data array
         * @param length number of elements
         * @param offset the index to begin updating the data
         *
         * @throws std::invalid_argument: if length or offset is negative
         * @throws std::invalid_argument: if length + offset is greater than buffer length
         * @throws std::invalid_argument: if length == 0 and indices is nullptr
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(const void *data, int32_t length, int32_t offset) const;

        /**
         * Sets the data in the buffer
         *
         * @param data a sequence of data points
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(std::span<int32_t> data);

        /**
         * Sets a subset of the data in the buffer
         *
         * @param data a sequence of data points
         * @param offset the index to begin updating the data
         *
         * @throws std::invalid_argument: if length + offset is greater than buffer length
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(std::span<int32_t> data, int32_t offset) const;

        /**
         * @return the structure of data in the buffer
         */
        [[nodiscard]] const BufferLayout &getLayout() const;

    protected:
        int32_t m_Length = 0;
        uint32_t m_RendererID = 0;

        BufferLayout m_Layout;

        [[nodiscard]] virtual uint32_t _getBufferTarget() const = 0;

        [[nodiscard]] virtual std::string _getBufferTarget(uint32_t target) const;

        [[nodiscard]] virtual uint32_t _getBufferUsage() const;

        [[nodiscard]] virtual std::string _getClassString() const;
    };
}
