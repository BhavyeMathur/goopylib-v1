#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"

#if __APPLE__

#include <OpenGL/gl3.h>

#endif

#include <GLFW/glfw3.h>


// Buffer
namespace gp {
    Buffer::Buffer(uint32_t count, const gp::BufferLayout &layout)
            : m_Count(count),
              m_Layout(layout) {
        GP_CORE_DEBUG("gp::Buffer::Buffer(layout)");
        if (glfwGetCurrentContext()) {
            init();
        }
    }

    void Buffer::init() {
        if (m_RendererID == 0) {
            glGenBuffers(1, &m_RendererID);
            GP_CORE_DEBUG("gp::Buffer::init({0})", m_RendererID);
        }
    }

    void Buffer::bind() const {
        glBindBuffer(_getBufferTarget(), m_RendererID);
    }

    Buffer::~Buffer() noexcept {
        if (m_RendererID == 0) {
            return;
        }

        glDeleteBuffers(1, &m_RendererID);
    }

    void Buffer::setData(const void *data, uint32_t count) {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data, count={1}", m_RendererID, count);

        bind();
        glBufferData(_getBufferTarget(), count * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }

    void Buffer::setData(const void *data, uint32_t count, uint32_t offset) const {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data", m_RendererID);

        bind();
        glBufferSubData(_getBufferTarget(), offset * m_Layout.m_Stride,
                        count * m_Layout.m_Stride, data);
    }
}


// Vertex Buffer
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

// Index Buffer
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
        #ifdef _MSC_VER
        auto *bufferData = new uint32_t[indices.size()];
        #else
        uint32_t bufferData[indices.size()];
        #endif

        std::copy(indices.begin(), indices.end(), bufferData);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices.size() * sizeof(uint32_t)), bufferData, GL_STATIC_DRAW);

        #ifdef _MSC_VER
        delete[] bufferData;
        #endif
    }

    void IndexBuffer::unbind() {
        GP_CORE_WARN("gp::IndexBuffer::unbind()");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::_getBufferTarget() const {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}

// Uniform Buffer
namespace gp {
    void UniformBuffer::unbind() {
        GP_CORE_WARN("gp::UniformBuffer::unbind()");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void UniformBuffer::setBinding(uint32_t binding) const {
        bind();
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    }

    uint32_t UniformBuffer::_getBufferTarget() const {
        return GL_UNIFORM_BUFFER;
    }
}
