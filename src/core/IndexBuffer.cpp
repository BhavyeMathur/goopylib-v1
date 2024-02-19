#define GP_LOGGING_LEVEL 3

#include "core/IndexBuffer.h"
#include "debug/Error.h"

#include <opengl.h>

namespace gp {
    IndexBuffer::IndexBuffer() : IndexBuffer{nullptr, 0} {
        GP_CORE_INFO("gp::IndexBuffer::IndexBuffer({0})", m_RendererID);
    }

    IndexBuffer::IndexBuffer(const int32_t *indices, const int32_t length)
        : Buffer{length, {{ShaderDataType::Int, "Index"}}} {
        GP_CORE_INFO("gp::IndexBuffer::IndexBuffer({0}, length={1})", m_RendererID, length);
        if (length != 0) {
            GP_CHECK_NOT_NULL(indices);
        }
    }

    IndexBuffer::IndexBuffer(std::span<int32_t> indices)
        : IndexBuffer{indices.data(), static_cast<int32_t>(indices.size())} {
        GP_CORE_INFO("gp::IndexBuffer::IndexBuffer({0}, length={1})", m_RendererID, indices.size());
    }

    IndexBuffer::IndexBuffer(const std::initializer_list<int32_t> indices)
        : IndexBuffer{data(indices), static_cast<int32_t>(indices.size())} {
    }

    uint32_t IndexBuffer::_getBufferTarget() const {
        return GL_ELEMENT_ARRAY_BUFFER;
    }

    uint32_t IndexBuffer::_getBufferUsage() const {
        return GL_STATIC_DRAW;
    }

    std::string IndexBuffer::_getClassString() const {
        return "IndexBuffer";
    }
}
