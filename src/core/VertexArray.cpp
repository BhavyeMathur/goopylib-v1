#define GP_LOG_OPENGL false
#define GP_LOGGING_LEVEL 3

#include "VertexArray.h"
#include "debug/Error.h"

#include <GLFW/glfw3.h>
#include <opengl.h>


namespace gp {
    GLenum shaderOpenGLType(ShaderDataType type);
}

namespace gp {
    VertexArray::VertexArray(const BufferLayout &layout)
        : m_VertexBuffer{layout} {
        GP_CORE_INFO("gp::VertexArray::VertexArray()");

        if (glfwGetCurrentContext()) {
            init();
        }
    }

    VertexArray::VertexArray(VertexArray &&other) noexcept
        : m_RendererID{std::exchange(other.m_RendererID, 0)},
          m_VertexBuffer{std::move(other.m_VertexBuffer)},
          m_IndexBuffer{std::move(other.m_IndexBuffer)} {
        GP_CORE_INFO("gp::VertexArray::VertexArray({0}) — move constructor", m_RendererID);
    }

    VertexArray::~VertexArray() {
        GP_CORE_INFO("gp::VertexArray::~VertexArray({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }

        GP_OPENGL("glDeleteVertexArrays(n=1, arrays={0})", m_RendererID);
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::init() {
        if (m_RendererID == 0) {
            GP_OPENGL("glGenVertexArrays(n=1)");
            glGenVertexArrays(1, &m_RendererID);
            GP_CORE_INFO("gp::VertexArray::init({0})", m_RendererID);
            GP_OPENGL("glGenVertexArrays(n=1) -> {0}", m_RendererID);

            bind();

            m_IndexBuffer.init();
            m_VertexBuffer.init();
            _setVertexAttribs();

            unbind();
        }
        else {
            GP_CORE_DEBUG("gp::VertexArray::init({0}) already initialized", m_RendererID);
        }
    }

    void VertexArray::bind() const {
        GP_CORE_TRACE("gp::VertexArray::bind({0})", m_RendererID);
        GP_CHECK_RENDERER_ID("gp::VertexArray::bind()");
        GP_CHECK_ACTIVE_CONTEXT("gp::VertexArray::bind()");

        GP_OPENGL("glBindVertexArray(array={0})", m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() {
        GP_CORE_TRACE("gp::VertexArray::unbind()");
        GP_CHECK_ACTIVE_CONTEXT("gp::VertexArray::bind()");

        GP_OPENGL("glBindVertexArray(array=0)");
        glBindVertexArray(0);
    }

    void VertexArray::draw(int32_t count, const int32_t mode) const {
        GP_CORE_DEBUG("gp::VertexArray::draw({0}, count={1}, mode={2})", m_RendererID, count, mode);
        GP_CHECK_GE(count, 0, "gp::VertexArray::draw() – count must be greater than or equal to 0");
        GP_CHECK_RENDERER_ID("gp::VertexArray::draw()");
        GP_CHECK_ACTIVE_CONTEXT("gp::VertexArray::draw()");

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
    void VertexArray::_setVertexAttribs() const {
        bind();
        m_VertexBuffer.bind();

        const BufferLayout layout = m_VertexBuffer.getLayout();

        uint32_t index = 0;
        const int32_t stride = layout.getStride();

        for (const BufferElement element: layout) {
            switch (const ShaderDataType type = element.getDataType()) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {
                    GP_OPENGL("glEnableVertexAttribArray({0})", index);
                    glEnableVertexAttribArray(index);

                    GP_OPENGL(
                        "glVertexAttribPointer({0}, size={1}, type=GL_FLOAT, normalised={2}, stride={3}, offset={4})",
                        index, element.getCount(), element.isNormalised(), stride, element.getOffset());
                    glVertexAttribPointer(index, element.getCount(), GL_FLOAT,
                                          element.isNormalized() ? GL_TRUE : GL_FALSE, stride,
                                          reinterpret_cast<const void *>(element.getOffset()));
                    index++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    GP_OPENGL("glEnableVertexAttribArray({0})", index);
                    glEnableVertexAttribArray(index);

                    GP_OPENGL("glVertexAttribIPointer({0}, size={1}, type={2}, stride={3}, offset={4})",
                              index, element.getCount(), shaderOpenGLType(type), stride, element.getOffset());
                    glVertexAttribIPointer(index, element.getCount(), shaderOpenGLType(type), stride,
                                           reinterpret_cast<const void *>(element.getOffset()));
                    index++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    const GLenum glType = shaderOpenGLType(type);
                    const bool normalized = element.isNormalized() ? GL_TRUE : GL_FALSE;
                    const int32_t size = element.getCount();
                    int32_t offset = element.getOffset();

                    for (int32_t i = 0; i < size; i++) {
                        GP_OPENGL("glEnableVertexAttribArray({0})", index);
                        glEnableVertexAttribArray(index);

                        GP_OPENGL(
                            "glVertexAttribPointer({0}, size={1}, type={2}, isNormalized={3}, stride={4}, offset={5})",
                            index, count, glType, normalized, stride, offset);
                        glVertexAttribPointer(index, size, glType, normalized, stride,
                                              reinterpret_cast<const void *>(offset));
                        glVertexAttribDivisor(index, 1);

                        offset += sizeof(float) * size * i;
                        index++;
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
