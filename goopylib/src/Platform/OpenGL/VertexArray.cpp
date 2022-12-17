#include "goopylib/Core/VertexArray.h"

namespace gp {
    VertexArray::VertexArray()
            : BaseVertexArray() {
        glGenVertexArrays(1, &m_RendererID);

        GP_CORE_DEBUG("Initialising Vertex Array {0}", m_RendererID);

        glBindVertexArray(m_RendererID);
    }

    VertexArray::VertexArray(uint32_t *indices, int32_t count) : BaseVertexArray() {
        GP_CORE_DEBUG("Generating Vertex Array");

        glGenVertexArrays(1, &m_RendererID);

        GP_CORE_DEBUG("Initialising Vertex Array {0}", m_RendererID);

        glBindVertexArray(m_RendererID);
        setIndexBuffer(CreateRef<IndexBuffer>(indices, count));
    }

    VertexArray::VertexArray(std::initializer_list<uint32_t> indices) {
        glGenVertexArrays(1, &m_RendererID);

        GP_CORE_DEBUG("Initialising Vertex Array {0}", m_RendererID);

        glBindVertexArray(m_RendererID);
        setIndexBuffer(CreateRef<IndexBuffer>(indices));
    }

    VertexArray::~VertexArray() {
        GP_CORE_DEBUG("Deallocating Vertex Array {0}", m_RendererID);
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() const {
        GP_CORE_WARN("Unbinding Vertex Arrays");
        glBindVertexArray(0);
    }

    void VertexArray::draw() const {
        bind();
        if (m_IndexBuffer) {
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->count(), GL_UNSIGNED_INT, nullptr);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, m_IndexBuffer->count());
        }
    }

    void VertexArray::draw(int32_t count) const {
        bind();
        if (m_IndexBuffer) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, count);
        }
    }

    void VertexArray::addVertexBuffer(const Ref<BaseVertexBuffer> &vertexBuffer) {
        bind();
        vertexBuffer->bind();

        const BufferLayout layout = vertexBuffer->getLayout();

        for (const BufferElement element: layout) {
            ShaderDataType type = element.getType();

            switch (type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {

                    GP_CORE_DEBUG(
                            "Vertex Array Attribute index={0}, size={1}, type=GL_FLOAT, normalized={2}, stride={3}, offset={4}",
                            m_VertexBufferIndex, element.getCount(), element.isNormalized(), layout.getStride(),
                            (const void *) element.m_Offset);

                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(m_VertexBufferIndex,
                                          element.getCount(),
                                          GL_FLOAT,
                                          element.isNormalized() ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (const void *) element.m_Offset);
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {

                    GP_CORE_DEBUG("Vertex Array Attribute index={0}, size={1}, type={2}, stride={3}, offset={4}",
                                  m_VertexBufferIndex, element.getCount(), shaderOpenGLType(type), layout.getStride(),
                                  (const void *) element.m_Offset);

                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribIPointer(m_VertexBufferIndex,
                                           element.getCount(),
                                           shaderOpenGLType(type),
                                           layout.getStride(),
                                           (const void *) element.m_Offset);
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    GLenum glType = shaderOpenGLType(element.getType());
                    bool isNormalized = element.isNormalized() ? GL_TRUE : GL_FALSE;
                    int32_t strideSize = layout.getStride();
                    int32_t count = element.getCount();

                    for (int32_t i = 0; i < count; i++) {

                        GP_CORE_DEBUG(
                                "Vertex Array Attribute index={0}, size={1}, type={2}, isNormalized={3}, strideSize={4}, offset={5}",
                                m_VertexBufferIndex, element.getCount(), shaderOpenGLType(type), isNormalized,
                                layout.getStride(), (const void *) (element.m_Offset + sizeof(float) * count * i));

                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex,
                                              count,
                                              glType,
                                              isNormalized,
                                              strideSize,
                                              (const void *) (element.m_Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_VertexBufferIndex, 1);
                        m_VertexBufferIndex++;
                    }
                    break;
                }
                default:
                    GP_CORE_ERROR("Unrecognised Shader Type");
                    return;
            }
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::setIndexBuffer(const Ref<BaseIndexBuffer> &indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }

    void VertexArray::setIndexBuffer(std::initializer_list<uint32_t> indices) {
        glBindVertexArray(m_RendererID);

        m_IndexBuffer = CreateRef<IndexBuffer>(indices);
    }
}
