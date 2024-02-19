#include "UniformBuffer.h"
#include "debug/Error.h"

#include <GLFW/glfw3.h>
#include <opengl.h>

namespace gp {
    UniformBuffer::UniformBuffer(const BufferLayout &layout)
        : Buffer{0, layout} {
        GP_CORE_INFO("gp::UniformBuffer::UniformBuffer({0})", m_RendererID);
    }

    void UniformBuffer::setBinding(const uint32_t binding) const {
        GP_CORE_INFO("gp::UniformBuffer::setBinding({0}, binding={1})", m_RendererID, binding);
        GP_CHECK_ACTIVE_CONTEXT("gp::UniformBuffer::setBinding()");
        GP_CHECK_RENDERER_ID("gp::UniformBuffer::setBinding()");

        bind();
        GP_OPENGL("glBindBufferBase(GL_UNIFORM_BUFFER, index={0}, buffer={1})", binding, m_RendererID);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    }

    uint32_t UniformBuffer::_getBufferTarget() const {
        return GL_UNIFORM_BUFFER;
    }

    std::string UniformBuffer::_getClassString() const {
        return "UniformBuffer";
    }
}
