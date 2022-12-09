#include "goopylib/Core/VertexArray.h"

namespace gp {
    VertexArray::VertexArray()
            : BaseVertexArray() {
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    std::shared_ptr<BaseVertexArray> VertexArray::create() {
        return std::make_shared<VertexArray>();
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const std::shared_ptr<BaseVertexBuffer> &vertexBuffer) {
        bind();
        vertexBuffer->bind();

        const auto &layout = vertexBuffer->getLayout();

        for (const auto &element: layout) {
            ShaderDataType type = element.getType();

            switch (type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {

                    std::cout << m_VertexBufferIndex << std::endl;
                    std::cout << element.getCount() << std::endl;
                    std::cout << element.isNormalized() << std::endl;
                    std::cout << layout.getStride() << std::endl;
                    std::cout << element.m_Offset << std::endl;

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
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribIPointer(m_VertexBufferIndex,
                                           element.getCount(),
                                           shaderOpenGLType(element.getType()),
                                           layout.getStride(),
                                           (const void *) element.m_Offset);
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    int count = element.getCount();

                    GLenum glType = shaderOpenGLType(element.getType());
                    bool normalized = element.isNormalized() ? GL_TRUE : GL_FALSE;
                    int stride = layout.getStride();

                    for (int i = 0; i < count; i++) {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex,
                                              count, glType, normalized, stride,
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

    void VertexArray::setIndexBuffer(const std::shared_ptr<BaseIndexBuffer> &indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }
}
