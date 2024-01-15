#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"


namespace gp {
    Buffer::Buffer(gp::Buffer &&other) noexcept
            : m_Count(std::exchange(other.m_Count, 0)),
              m_RendererID(std::exchange(other.m_RendererID, 0)),
              m_Layout(std::move(other.m_Layout)) {
        GP_CORE_DEBUG("gp::Buffer::Buffer() — move constructor");
    }

    uint32_t Buffer::count() const {
        return m_Count;
    }

    const BufferLayout &Buffer::getLayout() const {
        return m_Layout;
    }
}

namespace gp {
    UniformBuffer::UniformBuffer(const gp::BufferLayout &layout)
            : Buffer(0, layout) {

    }
}
