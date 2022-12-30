#include "goopylib/core/Buffer.h"

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


// Generic Buffer
namespace gp {
    Buffer::Buffer(uint32_t count)
            : m_Count(count) {
    }

    uint32_t Buffer::count() const {
        return m_Count;
    }
}

// Vertex Buffer
namespace gp {
    const BufferLayout &VertexBuffer::getLayout() const {
        return m_Layout;
    }

    void VertexBuffer::setLayout(const BufferLayout &layout) {
        GP_CORE_DEBUG("Setting Vertex Buffer layout");
        m_Layout = layout;
    }
}


// Uniform Buffer
namespace gp {
    const BufferLayout &UniformBuffer::getLayout() const {
        return m_Layout;
    }
}
