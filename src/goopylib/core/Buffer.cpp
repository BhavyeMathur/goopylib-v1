#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Buffer.h"
#include <opengl.h>
#include <GLFW/glfw3.h>


namespace gp {
    Buffer::Buffer(uint32_t count, const BufferLayout &layout)
        : m_Count(count),
          m_Layout(layout) {
        GP_CORE_DEBUG("gp::Buffer::Buffer(layout)");
        if (glfwGetCurrentContext()) {
            init();
        }
    }

    Buffer::Buffer(Buffer &&other) noexcept
        : m_Count(std::exchange(other.m_Count, 0)),
          m_RendererID(std::exchange(other.m_RendererID, 0)),
          m_Layout(std::move(other.m_Layout)) {
        GP_CORE_DEBUG("gp::Buffer::Buffer() — move constructor");
    }

    void Buffer::init() {
        if (m_RendererID == 0) {
            glGenBuffers(1, &m_RendererID);
            GP_CORE_DEBUG("gp::Buffer::init({0})", m_RendererID);
        }
    }

    void Buffer::bind() const {
        glBindBuffer(_getBufferTarget(), m_RendererID);
    }

    Buffer::~Buffer() noexcept {
        if (m_RendererID == 0) {
            return;
        }

        glDeleteBuffers(1, &m_RendererID);
    }

    void Buffer::setData(const void *data, uint32_t count) {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data, count={1}", m_RendererID, count);

        bind();
        glBufferData(_getBufferTarget(), count * m_Layout.m_Stride, data, GL_DYNAMIC_DRAW);

        m_Count = count;
    }

    void Buffer::setData(const void *data, uint32_t count, uint32_t offset) const {
        GP_CORE_TRACE("Setting Vertex Buffer {0} Data", m_RendererID);

        bind();
        glBufferSubData(_getBufferTarget(), offset * m_Layout.m_Stride,
                        count * m_Layout.m_Stride, data);
    }

    uint32_t Buffer::count() const {
        return m_Count;
    }

    const BufferLayout &Buffer::getLayout() const {
        return m_Layout;
    }
}
