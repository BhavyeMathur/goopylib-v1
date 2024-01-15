#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"

#if __APPLE__

#include <OpenGL/gl3.h>

#endif

#include <GLFW/glfw3.h>


// Vertex Buffer
namespace gp {
    VertexBuffer::VertexBuffer(const gp::BufferLayout &layout) :
            m_Layout(layout) {
        GP_CORE_DEBUG("gp::VertexBuffer::VertexBuffer(layout)");

        if (glfwGetCurrentContext()) {
            init();
        }
    }

    VertexBuffer::VertexBuffer(gp::VertexBuffer &&other) noexcept
            : Buffer(std::move(other)),
              m_Layout(std::move(other.m_Layout)) {
        GP_CORE_DEBUG("gp::VertexBuffer::VertexBuffer() — move constructor");
    }

    VertexBuffer::~VertexBuffer() {
        GP_CORE_DEBUG("gp::VertexBuffer::~VertexBuffer({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }

        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::init() {
        if (m_RendererID == 0) {
            glGenBuffers(1, &m_RendererID);
            GP_CORE_DEBUG("gp::VertexBuffer::init({0})", m_RendererID);
        }
    }

    void VertexBuffer::bind() const {
        GP_CORE_TRACE_ALL("gp::VertexBuffer::bind({0})", m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::unbind() {
        GP_CORE_WARN("gp::VertexBuffer::unbind()");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(const void *data, uint32_t count) {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data, count={1}", m_RendererID, count);

        bind();
        glBufferData(GL_ARRAY_BUFFER, count * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }

    void VertexBuffer::setData(const void *data, uint32_t count, uint32_t offset) const {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data", m_RendererID);

        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset * m_Layout.m_Stride,
                        count * m_Layout.m_Stride, data);
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
        GP_CORE_DEBUG("gp::IndexBuffer::IndexBuffer()");
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Index Buffer {0}, count={1}", m_RendererID, indices.size());

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

    IndexBuffer::IndexBuffer(gp::IndexBuffer &&other) noexcept
            : Buffer(std::move(other)) {

    }

    IndexBuffer::~IndexBuffer() {
        GP_CORE_DEBUG("gp::IndexBuffer::~IndexBuffer({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }

        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::bind() const {
        GP_CORE_TRACE_ALL("gp::IndexBuffer::bind({0})", m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::unbind() {
        GP_CORE_WARN("gp::IndexBuffer::unbind()");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

// Uniform Buffer
namespace gp {
    UniformBuffer::UniformBuffer(BufferLayout &&layout)
            : m_Layout(layout) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("gp::UniformBuffer::UniformBuffer({0})", m_RendererID);
    }

    UniformBuffer::UniformBuffer(gp::UniformBuffer &&other) noexcept
            : Buffer(std::move(other)),
              m_Layout(std::move(other.m_Layout)) {
        GP_CORE_DEBUG("gp::UniformBuffer::UniformBuffer() — move constructor");
    }

    UniformBuffer::~UniformBuffer() {
        if (m_RendererID == 0) {
            return;
        }

        glDeleteBuffers(1, &m_RendererID);
    }

    void UniformBuffer::bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    }

    void UniformBuffer::unbind() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBuffer::setData(const void *data, uint32_t count) {
        GP_CORE_TRACE("Setting Uniform Buffer {0} Data, count={1}", m_RendererID, count);

        bind();
        glBufferData(GL_UNIFORM_BUFFER, count * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }

    void UniformBuffer::setData(const void *data, uint32_t count, uint32_t offset) const {
        GP_CORE_TRACE("Setting Uniform Buffer {0} Data", m_RendererID);

        bind();
        glBufferSubData(GL_UNIFORM_BUFFER, offset * m_Layout.m_Stride,
                        count * m_Layout.m_Stride, data);
    }

    void UniformBuffer::setBinding(uint32_t binding) const {
        bind();
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    }
}
