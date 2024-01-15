#define GP_LOGGING_LEVEL 3
#include "src/goopylib/core/Buffer.h"


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
}


// Uniform Buffer
namespace gp {
    const BufferLayout &UniformBuffer::getLayout() const {
        return m_Layout;
    }
}
