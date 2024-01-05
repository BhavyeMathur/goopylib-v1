#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"
#include "src/goopylib/debug/LogMacros.h"


// Generic Buffer
namespace gp {
    Buffer::Buffer(uint32_t count)
            : m_Count(count) {
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
