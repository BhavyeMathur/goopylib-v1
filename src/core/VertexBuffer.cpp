#include "VertexBuffer.h"
#include <opengl.h>

namespace gp {
    VertexBuffer::VertexBuffer(const BufferLayout &layout)
            : Buffer(0, layout) {
    }

    uint32_t VertexBuffer::_getBufferTarget() const {
        return GL_ARRAY_BUFFER;
    }

    std::string VertexBuffer::_getClassString() const {
        return "VertexBuffer";
    }
}
