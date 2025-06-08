#define GP_LOGGING_LEVEL 3

#include "VertexBuffer.h"
#include <opengl.h>

namespace gp {
    VertexBuffer::VertexBuffer(const BufferLayout &layout)
            : Buffer{0, layout} {
        GP_CORE_INFO("gp::VertexBuffer::VertexBuffer({0})", m_RendererID);
    }

    uint32_t VertexBuffer::_getBufferTarget() const {
        return GL_ARRAY_BUFFER;
    }

    std::string VertexBuffer::_getClassString() const {
        return "VertexBuffer";
    }
}
