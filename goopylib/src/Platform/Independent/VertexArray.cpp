#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    const Ref<VertexBuffer> &VertexArray::getVertexBuffer() const {
        return m_VertexBuffer;
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        GP_CORE_TRACE_ALL("Setting VertexArray's Index Buffer");

        bind();
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }

    const Ref<IndexBuffer> &VertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
