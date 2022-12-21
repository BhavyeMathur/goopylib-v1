#include "BaseBuffer.h"

// Generic Buffer
namespace gp {
    BaseBuffer::BaseBuffer(uint32_t count)
            : m_Count(count) {

    }

    uint32_t BaseBuffer::count() const {
        return m_Count;
    }
}

// Base Vertex Buffer
namespace gp {
    BaseVertexBuffer::BaseVertexBuffer(uint32_t count)
            : BaseBuffer(count),
              m_Layout({}) {
        GP_CORE_INFO("Initializing BaseVertexBuffer, count={0}", count);
    }

    BaseVertexBuffer::~BaseVertexBuffer() {
        GP_CORE_INFO("Deallocating BaseVertexBuffer");
    }

    const BufferLayout &BaseVertexBuffer::getLayout() const {
        return m_Layout;
    }

    void BaseVertexBuffer::setLayout(const BufferLayout &layout) {
        GP_CORE_DEBUG("Setting BaseVertexBuffer layout");
        m_Layout = layout;
    }
}

// Base Index Buffer
namespace gp {
    BaseIndexBuffer::BaseIndexBuffer(uint32_t count)
            : BaseBuffer(count) {
        GP_CORE_INFO("Initializing BaseIndex Buffer");
    }

    BaseIndexBuffer::~BaseIndexBuffer() {
        GP_CORE_INFO("Deallocating BaseIndex Buffer");
    }
}
