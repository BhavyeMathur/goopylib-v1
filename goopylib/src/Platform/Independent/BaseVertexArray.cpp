#include "BaseVertexArray.h"

namespace gp {
    BaseVertexArray::BaseVertexArray() {
        GP_CORE_INFO("Initializing BaseVertex Array");
    }

    BaseVertexArray::~BaseVertexArray() {
        GP_CORE_INFO("Deallocating BaseVertex Array");
    }

    const std::vector<const Ref<BaseVertexBuffer>> & BaseVertexArray::getVertexBuffers() const {
        return m_VertexBuffers;
    }

    const std::shared_ptr<BaseIndexBuffer> &BaseVertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
