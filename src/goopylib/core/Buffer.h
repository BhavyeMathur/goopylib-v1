#pragma once

#include "gp.h"
#include "BufferLayout.h"

// Generic Buffer
namespace gp {
    class Buffer {
    public:
        GPAPI Buffer(uint32_t count, const BufferLayout &layout = {});

        GPAPI Buffer(const Buffer &) = delete;

        GPAPI Buffer(Buffer &&other) noexcept;

        GPAPI ~Buffer() noexcept;

        GPAPI void init();

        GPAPI void bind() const;

        [[nodiscard]] GPAPI uint32_t count() const;

        GPAPI void setData(const void *data, uint32_t count);

        GPAPI void setData(const void *data, uint32_t count, uint32_t offset) const;

        [[nodiscard]] GPAPI const BufferLayout &getLayout() const;

    protected:
        uint32_t m_Count = 0;
        uint32_t m_RendererID = 0;

        BufferLayout m_Layout;

        GPAPI virtual uint32_t _getBufferTarget() const = 0;
    };
}
