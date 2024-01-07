#define GP_LOGGING_LEVEL 3
#include "src/goopylib/core/VertexArray.h"

#if GP_USING_OPENGL

#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#endif


namespace gp {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_RendererID);

        GP_CORE_DEBUG("Initialising Vertex Array {0}", m_RendererID);

        glBindVertexArray(m_RendererID);
    }

    VertexArray::~VertexArray() {
        GP_CORE_DEBUG("Deallocating Vertex Array {0}", m_RendererID);
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::bind() const {
        GP_CORE_TRACE("Binding Vertex Array {0}", m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() {
        GP_CORE_WARN("Unbinding Vertex Arrays");
        glBindVertexArray(0);
    }

    void VertexArray::draw(int32_t count, int32_t mode) const {
        bind();
        if (m_IndexBuffer) {
            glDrawElements(mode,
                           count and count <= m_IndexBuffer->count() ? count : (int32_t) m_IndexBuffer->count(),
                           GL_UNSIGNED_INT,
                           nullptr);
        }
        else {
            glDrawArrays(mode, 0,
                         count and count <= m_VertexBuffer->count() ? count : (int32_t) m_VertexBuffer->count());
        }
    }

    void VertexArray::setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        bind();
        vertexBuffer->bind();

        m_VertexBuffer = vertexBuffer;
        uint32_t attrIndex = 0;

        const BufferLayout layout = vertexBuffer->getLayout();

        for (const BufferElement element: layout) {
            ShaderDataType type = element.getDataType();

            switch (type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {

                    GP_CORE_DEBUG(
                            "Vertex Array Attribute index={0}, size={1}, type=GL_FLOAT, normalized={2}, stride={3}, offset={4}",
                            attrIndex, element.getCount(), element.isNormalised(), layout.m_Stride,
                            (const void *) element.getOffset());

                    glEnableVertexAttribArray(attrIndex);
                    glVertexAttribPointer(attrIndex,
                                          element.getCount(),
                                          GL_FLOAT,
                                          element.isNormalised() ? GL_TRUE : GL_FALSE,
                                          layout.m_Stride,
                                          (const void *) element.getOffset());
                    attrIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {

                    GP_CORE_DEBUG("Vertex Array Attribute index={0}, size={1}, type={2}, stride={3}, offset={4}",
                                  attrIndex, element.getCount(), shaderOpenGLType(type), layout.m_Stride,
                                  (const void *) element.getOffset());

                    glEnableVertexAttribArray(attrIndex);
                    glVertexAttribIPointer(attrIndex,
                                           element.getCount(),
                                           shaderOpenGLType(type),
                                           layout.m_Stride,
                                           (const void *) element.getOffset());
                    attrIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {

                    GLenum glType = shaderOpenGLType(type);
                    bool normalized = element.isNormalised() ? GL_TRUE : GL_FALSE;
                    int32_t count = element.getCount();
                    int32_t stride = layout.m_Stride;

                    for (int32_t i = 0; i < count; i++) {

                        GP_CORE_DEBUG(
                                "Vertex Array Attribute index={0}, size={1}, type={2}, isNormalized={3}, strideSize={4}, offset={5}",
                                attrIndex, count, glType, normalized, stride,
                                (const void *) (element.getOffset() + sizeof(float) * count * i));

                        glEnableVertexAttribArray(attrIndex);
                        glVertexAttribPointer(attrIndex,
                                              count,
                                              glType,
                                              normalized,
                                              stride,
                                              (const void *) (element.getOffset() + sizeof(float) * count * i));
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
