#include "BaseVertexArray.h"

namespace gp {
    BaseVertexArray::BaseVertexArray() {
        GP_CORE_INFO("Initializing Vertex Array");
    }

    BaseVertexArray::~BaseVertexArray() {
        GP_CORE_INFO("Deallocating Vertex Array");
    }

    const std::vector<const BaseVertexBuffer*> & BaseVertexArray::getVertexBuffers() const {
        return m_VertexBuffers;
    }

    const std::shared_ptr<BaseIndexBuffer> &BaseVertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
