#include "goopylib/Core/Buffer.h"


// Vertex Buffer
namespace gp {
    // TODO allow non-float data types in VertexBuffer

    VertexBuffer::VertexBuffer(uint32_t count, void *vertices)
            : Buffer(count) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Vertex Buffer {0}, count={1}", m_RendererID, count);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, (long) (count * sizeof(float)), vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::initializer_list<float> vertices)
            : Buffer(vertices.size()) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Vertex Buffer {0}, count={1}", m_RendererID, vertices.size());

        float bufferData[vertices.size()];
        std::copy(vertices.begin(), vertices.end(), bufferData);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, (long) (vertices.size() * sizeof(float)), bufferData, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        GP_CORE_DEBUG("Deallocating Vertex Buffer {0}", m_RendererID);
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::bind() const {
        GP_CORE_TRACE_ALL("Binding Vertex Buffer {0}", m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::unbind() {
        GP_CORE_WARN("Unbinding Array Buffers");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(const void *data, uint32_t count) {
        GP_CORE_DEBUG("Setting Vertex Buffer {0} Data", m_RendererID);

        bind();
        glBufferData(GL_ARRAY_BUFFER, count * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }

    void VertexBuffer::setData(const void *data, uint32_t count, uint32_t offset) const {
        GP_CORE_DEBUG("Setting Vertex Buffer {0} Data", m_RendererID);

        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset * m_Layout.m_Stride,
                        count * m_Layout.m_Stride, data);
    }
}

// Index Buffer
namespace gp {
    IndexBuffer::IndexBuffer(uint32_t count, uint32_t *indices)
            : Buffer(count) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Index Buffer {0}", m_RendererID);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(std::initializer_list<uint32_t> indices)
            : Buffer(indices.size()) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Index Buffer {0}", m_RendererID);

        uint32_t bufferData[indices.size()];
        std::copy(indices.begin(), indices.end(), bufferData);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices.size() * sizeof(uint32_t)), bufferData, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        GP_CORE_DEBUG("Deallocating Index Buffer {0}", m_RendererID);
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::bind() const {
        GP_CORE_TRACE_ALL("Binding Index Buffer {0}", m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::unbind() {
        GP_CORE_WARN("Unbinding Element Array Buffers");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
