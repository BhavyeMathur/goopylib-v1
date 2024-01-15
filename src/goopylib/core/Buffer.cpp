#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"


// Generic Buffer
namespace gp {
    Buffer::Buffer(uint32_t count)
            : m_Count(count) {
    }

    Buffer::Buffer(gp::Buffer &&other) noexcept
            : m_Count(std::exchange(other.m_Count, 0)),
              m_RendererID(std::exchange(other.m_RendererID, 0)) {
        GP_CORE_DEBUG("gp::Buffer::Buffer() — move constructor");
    }

    uint32_t Buffer::count() const {
        return m_Count;
    }

}

// Vertex Buffer
namespace gp {
    const BufferLayout &VertexBuffer::getLayout() const {
        return m_Layout;
    }

    void VertexBuffer::setLayout(const BufferLayout &layout) {
        GP_CORE_DEBUG("Setting Vertex Buffer layout");
        m_Layout = layout;
    }
}


// Uniform Buffer
namespace gp {
    const BufferLayout &UniformBuffer::getLayout() const {
        return m_Layout;
    }
}
