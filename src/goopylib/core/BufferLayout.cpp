#include "BufferLayout.h"

#if (GP_LOG_BUFFER != true) and (GP_LOG_BUFFER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_BUFFER
#endif

#if !GP_VALUE_CHECK_BUFFER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


namespace gp {
    GLenum shaderOpenGLType(ShaderDataType type) {
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
                return GL_BOOL;

            case ShaderDataType::None:
                GP_CORE_ERROR("Unrecognised Shader Type");
                return 0;
        }
    }
}

// Buffer Layout Element
namespace gp {
    int32_t shaderTypeSize(ShaderDataType type) {
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
            case ShaderDataType::None:
                GP_CORE_ERROR("Unrecognised Shader Type");
                return 0;
        }
    }

    BufferElement::BufferElement(ShaderDataType type, const char *name, bool normalized)
            : m_Name(name),
              m_Type(type),
              m_Size(shaderTypeSize(type)),
              m_Offset(0),
              m_Normalized(normalized) {
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
                GP_CORE_ERROR("Unrecognised Shader Type");
                return 0;
        }
    }
}

// Buffer Layout
namespace gp {
    BufferLayout::BufferLayout(BufferElement *elements, int32_t count) {
        GP_CORE_INFO("Initializing BufferLayout");

        const gp::BufferElement *end = &elements[count];

        for (gp::BufferElement *element = elements; element != end; element++) {
            m_Elements.push_back(*element);
        }

        calculateOffsetAndStride();
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
            : m_Elements(elements) {
        GP_CORE_INFO("Initializing BufferLayout");

        calculateOffsetAndStride();
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

    void BufferLayout::calculateOffsetAndStride() {
        m_Stride = 0;
        m_Count = 0;

        for (auto &element: m_Elements) {
            element.m_Offset = m_Stride;
            m_Stride += element.m_Size;
            m_Count += element.getCount();
        }
    }
}
