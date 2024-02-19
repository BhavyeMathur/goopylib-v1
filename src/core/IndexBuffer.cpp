#include "core/IndexBuffer.h"
#include "debug/Error.h"

#include "opengl.h"

namespace gp {
    // TODO make length, indices order consistent in constructor & setData method
    IndexBuffer::IndexBuffer(const int32_t *indices, const int32_t length)
        : Buffer{length} {
        GP_CORE_INFO("gp::IndexBuffer::IndexBuffer({0}, length={1})", m_RendererID, length);
        if (length != 0) {
            GP_CHECK_NOT_NULL(indices);
        }

        if (m_RendererID != 0) {
            setData(indices, length);
        }
    }

    IndexBuffer::IndexBuffer(std::span<int32_t> indices)
        : IndexBuffer(indices.data(), indices.length()) {
    }

    IndexBuffer::IndexBuffer(const std::initializer_list<int32_t> indices)
        : Buffer(indices.size()) {
        GP_CORE_DEBUG("gp::IndexBuffer::IndexBuffer({0}, length={1})", m_RendererID, indices.size());

        if (m_RendererID != 0) {
            auto *bufferData = new uint32_t[indices.size()]; // TODO replace with std::array or unique ptr?
            std::copy(indices.begin(), indices.end(), bufferData);

            setData(bufferData, indices.size());
            delete[] bufferData;
        }
    }

    void IndexBuffer::setData(const void *data, const int32_t length) {
        GP_CORE_DEBUG("gp::IndexBuffer::setData({0}, length={1})", m_RendererID, length);
        if (length != 0) {
            GP_CHECK_NOT_NULL(data);
        }

        bind();
        glBufferData(_getBufferTarget(), static_cast<long>(length * sizeof(uint32_t)), data, GL_STATIC_DRAW);

        m_Length = length;
    }

    uint32_t IndexBuffer::_getBufferTarget() const {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}
