#define GP_LOG_OPENGL false
#define GP_LOGGING_LEVEL 3

#include "core/Core.h"
#include "core/Buffer.h"
#include "debug/Error.h"

#include <opengl.h>
#include <GLFW/glfw3.h>
#include <utility>


#define GP_BUFFER_TARGET _getBufferTarget(_getBufferTarget())


namespace gp {
    Buffer::Buffer(const int32_t length, const BufferLayout &layout)
        : m_Length{length},
          m_Layout{layout} {
        GP_CORE_INFO("gp::Buffer::Buffer(length={0}, layout)", length);
        GP_CHECK_GE(length, 0, "gp::Buffer::Buffer() – length must be greater than or equal to 0");
    }

    Buffer::Buffer(Buffer &&other) noexcept
        : m_Length{other.m_Length},
          m_RendererID{std::exchange(other.m_RendererID, 0)},
          m_Layout{std::move(other.m_Layout)} {
        GP_CORE_INFO("gp::{0}::Buffer({1}) — move constructor", _getClassString(other), m_RendererID);
    }

    Buffer::~Buffer() noexcept {
        GP_CORE_DEBUG("gp::Buffer::~Buffer({0})", m_RendererID);
        if (m_RendererID == 0) {
            return;
        }
        if (glfwGetCurrentContext()) {
            GP_OPENGL("glDeleteBuffers(n=1, buffers={0})", m_RendererID);
            glDeleteBuffers(1, &m_RendererID);
        }
    }

    void Buffer::init() {
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::init()");
        if (m_RendererID == 0) {
            GP_OPENGL("glGenBuffers(n=1)");
            glGenBuffers(1, &m_RendererID);
            GP_CORE_INFO("gp::{0}::init({1})", _getClassString(), m_RendererID);
            GP_OPENGL("glGenBuffers(n=1) -> {0}", m_RendererID);
        }
        else {
            GP_CORE_DEBUG("gp::{0}::init({1}) already initialized", _getClassString(), m_RendererID);
        }
        bind();
    }

    void Buffer::bind() const {
        GP_CORE_TRACE("gp::{0}::bind({1})", _getClassString(), m_RendererID);
        GP_CHECK_RENDERER_ID("gp::Buffer::bind()");
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::bind()");

        GP_OPENGL("glBindBuffer(target={0}, buffer={1})", GP_BUFFER_TARGET, m_RendererID);
        glBindBuffer(_getBufferTarget(), m_RendererID);
    }

    void Buffer::unbind() const {
        GP_CORE_WARN("gp::{0}::unbind({1})", _getClassString(), m_RendererID);
        GP_CHECK_ACTIVE_CONTEXT("gp::Buffer::unbind()");

        GP_OPENGL("glBindBuffer(target={0}, buffer=0)", GP_BUFFER_TARGET);
        glBindBuffer(_getBufferTarget(), 0);
    }

    int32_t Buffer::length() const {
        GP_CORE_TRACE("gp::{0}::length({1}) -> {2}", _getClassString(), m_RendererID, m_Length);
        return m_Length;
    }

    void Buffer::setData(const void *data, const int32_t length) {
        GP_CORE_DEBUG("gp::{0}::setData({1}, length={2})", _getClassString(), m_RendererID, length);

        GP_CHECK_GE(length, 0, "gp::Buffer::setData() – data length must be greater than or equal to 0");
        if (length != 0) {
            GP_CHECK_NOT_NULL(data);
        }

        bind();
        GP_OPENGL("glBufferData(target={0}, size={1}*{2}, data={3}, ...)",
                  GP_BUFFER_TARGET, length, m_Layout.getStride(), data);
        glBufferData(_getBufferTarget(), length * m_Layout.getStride(), data, _getBufferUsage());

        m_Length = length;
    }

    void Buffer::setData(const void *data, const int32_t length, const int32_t offset) const {
        GP_CORE_DEBUG("gp::{0}::setData({1}, length={2}, offset={3})", _getClassString(), m_RendererID, length, offset);

        GP_CHECK_GE(length, 0, "gp::Buffer::setData() – data length must be greater than or equal to 0");
        GP_CHECK_GE(offset, 0, "gp::Buffer::setData() – offset must be greater than or equal to 0");
        GP_CHECK_LE(length + offset, m_Length, "gp::Buffer::setData() – length + offset must be less than buffer size");
        if (length != 0) {
            GP_CHECK_NOT_NULL(data);
        }

        bind();
        GP_OPENGL("glBufferSubData(target={0}, offset={1}*{2}, size={3}*{2}, data={4})",
                  GP_BUFFER_TARGET, offset, m_Layout.getStride(), length, data);
        glBufferSubData(_getBufferTarget(), offset * m_Layout.getStride(), length * m_Layout.getStride(), data);
    }

    void Buffer::setData(const std::span<int32_t> data) {
        setData(data.data(), data.size());
    }

    void Buffer::setData(const std::span<int32_t> data, const int32_t offset) const {
        setData(data.data(), data.size(), offset);
    }

    const BufferLayout &Buffer::getLayout() const {
        GP_CORE_TRACE("gp::{0}::getLayout({1})", _getClassString(), m_RendererID);
        return m_Layout;
    }

    uint32_t Buffer::_getBufferUsage() const {
        return GL_DYNAMIC_DRAW;
    }

    std::string Buffer::_getClassString() const {
        return "Buffer";
    }

    std::string Buffer::_getBufferTarget(const uint32_t target) const {
        switch (target) {
            case GL_ELEMENT_ARRAY_BUFFER:
                return "GL_ELEMENT_ARRAY_BUFFER";
            case GL_ARRAY_BUFFER:
                return "GL_ARRAY_BUFFER";
            case GL_UNIFORM_BUFFER:
                return "GL_UNIFORM_BUFFER";
            default:
                GP_VALUE_ERROR("Unknown buffer target {0}", target);
                return "Unknown";
        }
    }
}

#undef GP_BUFFER_TARGET
