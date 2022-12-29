#include "goopylib/core/Buffer.h"

#if !GP_LOG_BUFFER
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_BUFFER
#undef GP_VALUE_CHECKING
#endif

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
