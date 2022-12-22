#include "src/goopylib/Core/Buffer.h"

// Generic Buffer
namespace gp {
    Buffer::Buffer(uint32_t count)
            : m_Count(count) {

    }

    uint32_t Buffer::count() const {
        return m_Count;
    }
}

// Base Vertex Buffer
namespace gp {
    const BufferLayout &VertexBuffer::getLayout() const {
        return m_Layout;
    }

    void VertexBuffer::setLayout(const BufferLayout &layout) {
        GP_CORE_DEBUG("Setting VertexBuffer layout");
        m_Layout = layout;
    }
}

// Base Index Buffer
namespace gp {
    BaseIndexBuffer::BaseIndexBuffer(uint32_t count)
            : Buffer(count) {
        GP_CORE_INFO("Initializing BaseIndex Buffer");
    }

    BaseIndexBuffer::~BaseIndexBuffer() {
        GP_CORE_INFO("Deallocating BaseIndex Buffer");
    }
}
