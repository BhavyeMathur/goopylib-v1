#define GP_LOGGING_LEVEL 3

#include "BufferLayout.h"
#include "debug/Error.h"

#include <opengl.h>

namespace gp {
    GLenum shaderOpenGLType(const ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;

            case ShaderDataType::Bool:
                return GL_BYTE;

            default:
                GP_CORE_ERROR("gp::shaderOpenGLType() Unrecognised Shader Type");
                return 0;
        }
    }
}

// Buffer Layout Element
namespace gp {
    int32_t shaderTypeSize(const ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                GP_CORE_ERROR("gp::shaderTypeSize() Unrecognised Shader Type");
                return 0;
        }
    }

    BufferElement::BufferElement(const ShaderDataType type, const char *name, const bool normalized)
        : m_Name(name),
          m_Type(type),
          m_Size(shaderTypeSize(type)),
          m_Normalized(normalized) {
    }

    const char *BufferElement::getName() const {
        return m_Name;
    }

    ShaderDataType BufferElement::getDataType() const {
        return m_Type;
    }

    int32_t BufferElement::getCount() const {
        switch (m_Type) {
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3; // 3* float3
            case ShaderDataType::Mat4:
                return 4; // 4* float4
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::None:
            default:
                GP_CORE_ERROR("Unrecognised Shader Type");
                return 0;
        }
    }

    int32_t BufferElement::getSize() const {
        return m_Size;
    }

    int32_t BufferElement::getOffset() const {
        return m_Offset;
    }

    bool BufferElement::isNormalized() const {
        return m_Normalized;
    }
}

// Buffer Layout
namespace gp {
    BufferLayout::BufferLayout(const BufferElement *elements, const int32_t count) {
        GP_CORE_INFO("gp::BufferLayout::BufferLayout({0}, count={1})", reinterpret_cast<std::uintptr_t>(elements), count);

        const BufferElement *end = &elements[count];

        for (const BufferElement *element = elements; element != end; element++) {
            m_Elements.push_back(*element);
        }

        _calculateOffsetAndStride();
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement> elements)
        : m_Elements{elements} {
        GP_CORE_INFO("gp::BufferLayout::BufferLayout(count={0})", elements.size());

        _calculateOffsetAndStride();
    }

    int32_t BufferLayout::getStride() const {
        return m_Stride;
    }

    int32_t BufferLayout::getCount() const {
        return m_Count;
    }

    std::vector<BufferElement>::iterator BufferLayout::begin() {
        return m_Elements.begin();
    }

    std::vector<BufferElement>::iterator BufferLayout::end() {
        return m_Elements.end();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
        return m_Elements.begin();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::end() const {
        return m_Elements.end();
    }

    void BufferLayout::_calculateOffsetAndStride() {
        m_Stride = 0;
        m_Count = 0;

        for (auto &element: m_Elements) {
            element.m_Offset = m_Stride;
            m_Stride += element.getSize();
            m_Count += element.getCount();
        }
    }
}
