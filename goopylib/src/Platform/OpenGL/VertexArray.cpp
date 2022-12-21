#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    VertexArray::VertexArray()
            : BaseVertexArray() {
        glGenVertexArrays(1, &m_RendererID);

        GP_CORE_DEBUG("Initialising Vertex Array {0}", m_RendererID);

        glBindVertexArray(m_RendererID);
    }

    VertexArray::~VertexArray() {
        GP_CORE_DEBUG("Deallocating Vertex Array {0}", m_RendererID);
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::bind() const {
        GP_CORE_TRACE_ALL("Binding Vertex Array {0}", m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() const {
        GP_CORE_WARN("Unbinding Vertex Arrays");
        glBindVertexArray(0);
    }

    void VertexArray::draw(int32_t count) const {
        bind();
        if (m_IndexBuffer) {
            glDrawElements(GL_TRIANGLES, count ? count : (int32_t) m_IndexBuffer->count(), GL_UNSIGNED_INT, nullptr);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, count ? count : (int32_t) m_VertexBuffer->count());
        }
    }

    void VertexArray::setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        bind();
        vertexBuffer->bind();

        m_VertexBuffer = vertexBuffer;
        uint32_t attrIndex = 0;

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
                            attrIndex, element.getCount(), element.isNormalized(), layout.getStride(),
                            (const void *) element.m_Offset);

                    glEnableVertexAttribArray(attrIndex);
                    glVertexAttribPointer(attrIndex,
                                          element.getCount(),
                                          GL_FLOAT,
                                          element.isNormalized() ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (const void *) element.m_Offset);
                    attrIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {

                    GP_CORE_DEBUG("Vertex Array Attribute index={0}, size={1}, type={2}, stride={3}, offset={4}",
                                  attrIndex, element.getCount(), shaderOpenGLType(type), layout.getStride(),
                                  (const void *) element.m_Offset);

                    glEnableVertexAttribArray(attrIndex);
                    glVertexAttribIPointer(attrIndex,
                                           element.getCount(),
                                           shaderOpenGLType(type),
                                           layout.getStride(),
                                           (const void *) element.m_Offset);
                    attrIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {

                    GLenum glType = shaderOpenGLType(type);
                    bool normalized = element.isNormalized() ? GL_TRUE : GL_FALSE;
                    int32_t count = element.getCount();
                    int32_t stride = layout.getStride();

                    for (int32_t i = 0; i < count; i++) {

                        GP_CORE_DEBUG(
                                "Vertex Array Attribute index={0}, size={1}, type={2}, isNormalized={3}, strideSize={4}, offset={5}",
                                attrIndex, count, glType, normalized, stride,
                                (const void *) (element.m_Offset + sizeof(float) * count * i));

                        glEnableVertexAttribArray(attrIndex);
                        glVertexAttribPointer(attrIndex,
                                              count,
                                              glType,
                                              normalized,
                                              stride,
                                              (const void *) (element.m_Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(attrIndex, 1);
                        attrIndex++;
                    }
                    break;
                }
                default:
                    GP_CORE_ERROR("Unrecognised Shader Type");
            }
        }
    }
}
