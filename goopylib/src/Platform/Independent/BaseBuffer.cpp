#include "BaseBuffer.h"

// Base Vertex Buffer
namespace gp {
    BaseVertexBuffer::BaseVertexBuffer()
    : m_Layout({}) {
        GP_CORE_INFO("Initializing Empty BaseVertexBuffer");
    }

    BaseVertexBuffer::BaseVertexBuffer(int32_t count)
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
    BaseIndexBuffer::BaseIndexBuffer(int32_t count)
            : BaseBuffer(count) {
        GP_CORE_INFO("Initializing BaseIndex Buffer");
    }

    BaseIndexBuffer::~BaseIndexBuffer() {
        GP_CORE_INFO("Deallocating BaseIndex Buffer");
    }
}
