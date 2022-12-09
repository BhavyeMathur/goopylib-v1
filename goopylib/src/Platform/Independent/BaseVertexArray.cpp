#include "BaseVertexArray.h"

namespace gp {
    const std::vector<std::shared_ptr<BaseVertexBuffer>> &BaseVertexArray::getVertexBuffers() const {
        return m_VertexBuffers;
    }

    const std::shared_ptr<BaseIndexBuffer> &BaseVertexArray::getIndexBuffer() const {
        return m_IndexBuffer;
    }
}
