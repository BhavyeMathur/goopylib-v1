#define GP_LOG_OPENGL false
#define GP_LOGGING_LEVEL 3

#include "core/VertexArray.h"

#include <GLFW/glfw3.h>
#include <opengl.h>


namespace gp {
    GLenum shaderOpenGLType(ShaderDataType type);
}

namespace gp {
    VertexArray::VertexArray(const BufferLayout &layout)
        : m_VertexBuffer{layout} {
        GP_CORE_DEBUG("gp::VertexArray::VertexArray()");

        if (glfwGetCurrentContext()) {
            init();
        }
    }

    VertexArray::VertexArray(VertexArray &&other) noexcept
        : m_RendererID{std::exchange(other.m_RendererID, 0)},
          m_VertexBuffer{std::move(other.m_VertexBuffer)},
          m_IndexBuffer{std::move(other.m_IndexBuffer)} {
        GP_CORE_DEBUG("gp::VertexArray::VertexArray(gp::VertexArray &&other)");
    }

    VertexArray::~VertexArray() {
        GP_CORE_DEBUG("gp::VertexArray::~VertexArray()", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }

        GP_OPENGL("glDeleteVertexArrays(n=1, arrays={0})", m_RendererID);
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::init() {
        GP_CORE_DEBUG("gp::VertexArray::init()");
        if (m_RendererID == 0) {
            GP_OPENGL("glGenVertexArrays(n=1)");
            glGenVertexArrays(1, &m_RendererID);
            GP_OPENGL("glGenVertexArrays(n=1) -> {0}", m_RendererID);

            bind();

            m_IndexBuffer.init();
            m_VertexBuffer.init();
            _setVertexAttribs();

            unbind();
        }
    }

    void VertexArray::bind() const {
        GP_CORE_TRACE("gp::VertexArray::bind({0})", m_RendererID);
        GP_OPENGL("glBindVertexArray(array={0})", m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() {
        GP_CORE_TRACE("gp::VertexArray::unbind()");
        GP_OPENGL("glBindVertexArray(array=0)");
        glBindVertexArray(0);
    }

    void VertexArray::draw(int32_t count, int32_t mode) const {
        GP_CORE_TRACE("gp::VertexArray::draw({0}, count={1}, mode={2})", m_RendererID, count, mode);

        bind();
        if (m_IndexBuffer.length()) {
            count = count <= m_IndexBuffer.length() ? count : m_IndexBuffer.length();
            GP_OPENGL("glDrawElements(..., count={0}, type=GL_UNSIGNED_INT, indices=nullptr)", count);
            glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
        }
        else {
            count = count <= m_VertexBuffer.length() ? count : m_VertexBuffer.length();
            GP_OPENGL("glDrawArrays(..., first=0, count={0})", count);
            glDrawArrays(mode, 0, count <= m_VertexBuffer.length() ? count : m_VertexBuffer.length());
        }
        unbind();
    }
}

namespace gp {
    VertexBuffer &VertexArray::getVertexBuffer() {
        GP_CORE_TRACE_ALL("VertexArray::getVertexBuffer()");
        return m_VertexBuffer;
    }

    IndexBuffer &VertexArray::getIndexBuffer() {
        GP_CORE_TRACE_ALL("VertexArray::getIndexBuffer()");
        return m_IndexBuffer;
    }
}

namespace gp {
    void VertexArray::_setVertexAttribs() {
        bind();
        m_VertexBuffer.bind();

        uint32_t attrIndex = 0;

        const BufferLayout layout = m_VertexBuffer.getLayout();

        for (const BufferElement element: layout) {
            ShaderDataType type = element.getDataType();

            switch (type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {
                    GP_OPENGL("glEnableVertexAttribArray({0})", attrIndex);
                    glEnableVertexAttribArray(attrIndex);

                    GP_OPENGL(
                        "glVertexAttribPointer({0}, size={1}, type=GL_FLOAT, normalised={2}, stride={3}, offset={4})",
                        attrIndex, element.getCount(), element.isNormalised(), layout.getStride(), element.getOffset());
                    glVertexAttribPointer(attrIndex,
                                          element.getCount(),
                                          GL_FLOAT,
                                          element.isNormalized() ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (const void *) element.getOffset());
                    attrIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    GP_OPENGL("glEnableVertexAttribArray({0})", attrIndex);
                    glEnableVertexAttribArray(attrIndex);

                    GP_OPENGL(
                        "glVertexAttribIPointer({0}, size={1}, type={2}, stride={3}, offset={4})",
                        attrIndex, element.getCount(), shaderOpenGLType(type), layout.getStride(), element.getOffset());
                    glVertexAttribIPointer(attrIndex,
                                           element.getCount(),
                                           shaderOpenGLType(type),
                                           layout.getStride(),
                                           (const void *) element.getOffset());
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
                        GP_OPENGL("glEnableVertexAttribArray({0})", attrIndex);
                        glEnableVertexAttribArray(attrIndex);

                        GP_OPENGL(
                            "glVertexAttribPointer({0}, size={1}, type={2}, isNormalized={3}, stride={4}, offset={5})",
                            attrIndex, count, glType, normalized, stride,
                            element.getOffset() + sizeof(float) * count * i);
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
        unbind();
    }
}
