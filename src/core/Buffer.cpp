#define GP_LOGGING_LEVEL 4

#include "core/Core.h"
#include "core/Buffer.h"
#include "debug/Error.h"

#include <opengl.h>
#include <GLFW/glfw3.h>
#include <utility>


namespace gp {
    Buffer::Buffer(const int32_t length, const BufferLayout &layout)
        : m_Length{length},
          m_Layout{layout} {
        GP_CORE_INFO("gp::Buffer::Buffer(layout)");
        GP_CHECK_INITIALISED("gp::Buffer::Buffer()");
        GP_CHECK_GE(length, 0, "gp::Buffer::Buffer() – length must be greater than or equal to 0");

        if (glfwGetCurrentContext()) {
            init();
        }
    }

    Buffer::Buffer(Buffer &&other) noexcept
        : m_Length{other.m_Length},
          m_RendererID{std::exchange(other.m_RendererID, 0)},
          m_Layout{std::move(other.m_Layout)} {
        GP_CORE_INFO("gp::Buffer::Buffer() — move constructor");
    }

    void Buffer::init() {
        GP_CORE_INFO("gp::Buffer::init({0})", m_RendererID);
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::init()");
        if (m_RendererID == 0) {
            glGenBuffers(1, &m_RendererID);
        }
    }

    void Buffer::bind() const {
        GP_CORE_TRACE("gp::Buffer::bind({0})", m_RendererID);
        GP_CHECK_NOT_EQUALS(m_RendererID, 0, "gp::Buffer::bind() – cannot bind uninitialised buffer");
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::bind()");
        glBindBuffer(_getBufferTarget(), m_RendererID);
    }

    void Buffer::unbind() const {
        GP_CORE_WARN("gp::Buffer::unbind({0})", m_RendererID);
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::unbind()");
        glBindBuffer(_getBufferTarget(), 0);
    }

    Buffer::~Buffer() noexcept {
        GP_CORE_DEBUG("gp::Buffer::~Buffer({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }
        if (glfwGetCurrentContext()) {
            glDeleteBuffers(1, &m_RendererID);
        }
    }

    int32_t Buffer::length() const {
        GP_CORE_TRACE("gp::Buffer::length{0})", m_RendererID);
        return m_Length;
    }

    void Buffer::setData(const void *data, const int32_t length) {
        GP_CORE_DEBUG("gp::Buffer::setData({0}, length={1})", m_RendererID, length);

        GP_CHECK_GE(length, 0, "gp::Buffer::setData() – data length must be greater than or equal to 0");
        if (length != 0) {
            GP_CHECK_NOT_NULL(data);
        }

        bind();
        glBufferData(_getBufferTarget(), length * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Length = length;
    }

    void Buffer::setData(const void *data, const int32_t length, const int32_t offset) const {
        GP_CORE_DEBUG("gp::Buffer::setData({0}, length={1}, offset={2})", m_RendererID, length, offset);

        GP_CHECK_GE(length, 0, "gp::Buffer::setData() – data length must be greater than or equal to 0");
        GP_CHECK_GE(offset, 0, "gp::Buffer::setData() – offset must be greater than or equal to 0");
        GP_CHECK_GE(length + offset, m_Length, "gp::Buffer::setData() – length + offset must be less than buffer size");
        if (length != 0) {
            GP_CHECK_NOT_NULL(data);
        }

        bind();
        glBufferSubData(_getBufferTarget(), offset * m_Layout.m_Stride, length * m_Layout.m_Stride, data);
    }

    const BufferLayout &Buffer::getLayout() const {
        GP_CORE_TRACE("gp::Buffer::getLayout({0})", m_RendererID);
        return m_Layout;
    }
}
