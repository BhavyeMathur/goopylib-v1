#include "src/goopylib/core/VertexArray.h"

#if !GP_LOG_VERTEX_ARRAY
#undef GP_LOGGING
#endif

#include "src/goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_VERTEX_ARRAY
#undef GP_VALUE_CHECKING
#endif

#include "src/goopylib/debug/Error.h"


namespace gp {
    const Ref<VertexBuffer> &VertexArray::getVertexBuffer() const {
        return m_VertexBuffer;
    }

    void VertexArray::setIndexBuffer(std::initializer_list<uint32_t> indices) {
        GP_CORE_TRACE_ALL("Setting VertexArray's Index Buffer");

        bind();
        m_IndexBuffer = Ref<IndexBuffer>(new IndexBuffer(indices));
    }

    void VertexArray::setIndexBuffer(uint32_t count, uint32_t *indices) {
        GP_CORE_TRACE_ALL("Setting VertexArray's Index Buffer");

        bind();
        m_IndexBuffer = Ref<IndexBuffer>(new IndexBuffer(count, indices));
    }

    const Ref<IndexBuffer> &VertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
