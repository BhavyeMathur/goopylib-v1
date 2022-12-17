#include "BaseVertexArray.h"

namespace gp {
    BaseVertexArray::BaseVertexArray() {
        GP_CORE_INFO("Initializing BaseVertex Array");
    }

    BaseVertexArray::~BaseVertexArray() {
        GP_CORE_INFO("Deallocating BaseVertex Array");
    }

    const Ref <VertexBuffer> & BaseVertexArray::getVertexBuffer() const {
        return m_VertexBuffer;
    }

    void BaseVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        GP_CORE_TRACE("Setting VertexArray's Index Buffer");

        bind();
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }

    void BaseVertexArray::setIndexBuffer(std::initializer_list<uint32_t> indices) {
        GP_CORE_TRACE("Setting VertexArray's Index Buffer");

        bind();
        m_IndexBuffer = CreateRef<IndexBuffer>(indices);
    }

    const Ref<IndexBuffer> &BaseVertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
