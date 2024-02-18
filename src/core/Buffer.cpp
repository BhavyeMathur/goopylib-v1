#define GP_LOGGING_LEVEL 3

#include "core/Buffer.h"

#include <opengl.h>
#include <GLFW/glfw3.h>
#include <utility>


namespace gp {
    Buffer::Buffer(const int32_t length, const BufferLayout &layout)
        : m_Length{length},
          m_Layout{layout} {
        GP_CORE_INFO("gp::Buffer::Buffer(layout)");
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
        if (m_RendererID == 0) {
            glGenBuffers(1, &m_RendererID);
        }
    }

    void Buffer::bind() const {
        GP_CORE_TRACE("gp::Buffer::bind({0})", m_RendererID);
        glBindBuffer(_getBufferTarget(), m_RendererID);
    }

    void Buffer::unbind() const {
        GP_CORE_WARN("gp::Buffer::unbind({0})", m_RendererID);
        glBindBuffer(_getBufferTarget(), 0);
    }

    Buffer::~Buffer() noexcept {
        GP_CORE_DEBUG("gp::Buffer::~Buffer({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }
        glDeleteBuffers(1, &m_RendererID);
    }

    int32_t Buffer::length() const {
        GP_CORE_TRACE("gp::Buffer::length{0})", m_RendererID);
        return m_Length;
    }

    void Buffer::setData(const void *data, const int32_t length) {
        GP_CORE_DEBUG("gp::Buffer::setData({0}, length={1})", m_RendererID, length);

        bind();
        glBufferData(_getBufferTarget(), length * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Length = length;
    }

    void Buffer::setData(const void *data, const int32_t length, const int32_t offset) const {
        GP_CORE_DEBUG("gp::Buffer::setData({0}, length={1}, offset={2})", m_RendererID, length, offset);

        bind();
        glBufferSubData(_getBufferTarget(), offset * m_Layout.m_Stride, length * m_Layout.m_Stride, data);
    }

    const BufferLayout &Buffer::getLayout() const {
        GP_CORE_TRACE("gp::Buffer::getLayout({0})", m_RendererID);
        return m_Layout;
    }
}
