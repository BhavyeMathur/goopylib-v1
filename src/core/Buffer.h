#pragma once

#include "gp.h"
#include "BufferLayout.h"
#include <span>


namespace gp {
    class GPAPI Buffer {
    public:
        Buffer(int32_t length, const BufferLayout &layout);

        Buffer(const Buffer &) = delete;

        Buffer(Buffer &&other) noexcept;

        virtual ~Buffer() noexcept;

        void init();

        void bind() const;

        void unbind() const;

        [[nodiscard]] int32_t length() const;

        void setData(const void *data, int32_t length);

        void setData(const void *data, int32_t length, int32_t offset) const;

        void setData(std::span<int32_t> data);

        void setData(std::span<int32_t> data, int32_t offset) const;

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
