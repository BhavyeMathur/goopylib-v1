#pragma once

#include "gp.h"
#include "BufferLayout.h"


namespace gp {
    class GPAPI Buffer {
    public:
        Buffer(size_t length, const BufferLayout &layout = {});

        Buffer(const Buffer &) = delete;

        Buffer(Buffer &&other) noexcept;

        virtual ~Buffer() noexcept;

        void init();

        void bind() const;

        void unbind() const;

        [[nodiscard]] size_t length() const;

        void setData(const void *data, size_t length);

        void setData(const void *data, size_t length, size_t offset) const;

        [[nodiscard]] const BufferLayout &getLayout() const;

    protected:
        size_t m_Length = 0;
        uint32_t m_RendererID = 0;

        BufferLayout m_Layout;

        [[nodiscard]] virtual uint32_t _getBufferTarget() const = 0;

        [[nodiscard]] virtual uint32_t _getBufferUsage() const;
    };
}
