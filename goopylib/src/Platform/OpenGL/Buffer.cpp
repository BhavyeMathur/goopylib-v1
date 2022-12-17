#include "goopylib/Core/Buffer.h"


// Vertex Buffer
namespace gp {
    VertexBuffer::VertexBuffer(int32_t count, float *vertices)
            : BaseVertexBuffer(count) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Vertex Buffer {0}, count={1}", m_RendererID, count);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, (long) (count * sizeof(float)), vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::initializer_list<float> vertices)
            : BaseVertexBuffer((int32_t) vertices.size()) {
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
        GP_CORE_TRACE("Binding Vertex Buffer {0}", m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::unbind() const {
        GP_CORE_WARN("Unbinding Array Buffers");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(const float *data, int32_t count) {
        GP_CORE_DEBUG("Setting Vertex Buffer {0} Data", m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, (long) (count * sizeof(float)), data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }
}

// Index Buffer
namespace gp {
    IndexBuffer::IndexBuffer(int32_t count, uint32_t *indices)
            : BaseIndexBuffer(count) {
        glGenBuffers(1, &m_RendererID);

        GP_CORE_DEBUG("Initializing Index Buffer {0}", m_RendererID);

        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(std::initializer_list<uint32_t> indices)
            : BaseIndexBuffer((int32_t) indices.size()) {
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
        GP_CORE_TRACE("Binding Index Buffer {0}", m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::unbind() const {
        GP_CORE_WARN("Unbinding Element Array Buffers");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
