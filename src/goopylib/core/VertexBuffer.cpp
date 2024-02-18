#include "VertexBuffer.h"
#include <opengl.h>

namespace gp {
    VertexBuffer::VertexBuffer(const gp::BufferLayout &layout)
            : Buffer(0, layout) {
    }

    void VertexBuffer::unbind() {
        GP_CORE_WARN("gp::VertexBuffer::unbind()");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    uint32_t VertexBuffer::_getBufferTarget() const {
        return GL_ARRAY_BUFFER;
    }
}
