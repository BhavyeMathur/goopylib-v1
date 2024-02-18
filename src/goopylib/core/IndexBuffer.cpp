#include "IndexBuffer.h"

#include "opengl.h"

namespace gp {
    IndexBuffer::IndexBuffer(uint32_t count, uint32_t *indices)
        : Buffer(count) {
        GP_CORE_DEBUG("gp::IndexBuffer::IndexBuffer()");

        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Index Buffer {0}, count={1}", m_RendererID, count);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(std::initializer_list<uint32_t> indices)
        : Buffer(indices.size()) {
        GP_CORE_DEBUG("gp::IndexBuffer::IndexBuffer({0}, count={1})", m_RendererID, indices.size());

        // TODO replace with std::array or unique ptr?
        auto *bufferData = new uint32_t[indices.size()];

        std::copy(indices.begin(), indices.end(), bufferData);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices.size() * sizeof(uint32_t)), bufferData, GL_STATIC_DRAW);

        delete[] bufferData;
    }

    void IndexBuffer::unbind() {
        GP_CORE_WARN("gp::IndexBuffer::unbind()");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::_getBufferTarget() const {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}
