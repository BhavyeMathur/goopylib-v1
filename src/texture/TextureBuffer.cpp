#define GP_LOGGING_LEVEL 3

#include "TextureBuffer.h"
#include "Bitmap.h"
#include "debug/Error.h"

#include <opengl.h>
#include <GLFW/glfw3.h>


namespace gp {
    int32_t TextureBuffer::s_TextureSlots = 0;

    TextureBuffer::TextureBuffer(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data)
            : m_Width(width),
              m_Height(height),
              m_Channels(channels) {
        GP_CHECK_ACTIVE_CONTEXT("gp::TextureBuffer::TextureBuffer()");

        GP_OPENGL("glGenTextures(1)");
        glGenTextures(1, &m_RendererID);
        bind(0);

        GP_OPENGL("glPixelStorei(GL_UNPACK_ALIGNMENT, 1)");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GP_OPENGL("glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        GP_OPENGL("glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GP_OPENGL("glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        GP_OPENGL("glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (data)
            setData(m_Width, m_Height, m_Channels, data);
    }

    TextureBuffer::TextureBuffer(const Bitmap &bitmap)
            : TextureBuffer(bitmap.getWidth(), bitmap.getHeight(), bitmap.getChannels(), bitmap.getData()) {
    }

    TextureBuffer::~TextureBuffer() {
        GP_CORE_DEBUG("gp::Texture2D::~Texture2D()");
        glDeleteTextures(1, &m_RendererID);
    }

    void TextureBuffer::init() {
        GP_CHECK_ACTIVE_CONTEXT("gp::TextureBuffer::init()");
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_TextureSlots);
    }

    void TextureBuffer::bind(uint32_t slot) const {
        GP_CORE_TRACE_ALL("gp::TextureBuffer::bind({1}) - '{0}'", slot, m_Path);
        GP_CHECK_RENDERER_ID("gp::TextureBuffer::bind()");
        GP_CHECK_ACTIVE_CONTEXT("gp::TextureBuffer::bind()");

        GP_OPENGL("glActiveTexture(GL_TEXTURE0 + {0})", slot);
        glActiveTexture(GL_TEXTURE0 + slot);

        GP_OPENGL("glBindTexture(GL_TEXTURE2D, buffer={0})", m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void TextureBuffer::unbind() {
        GP_CORE_WARN("gp::Texture2D::unbind()");

        GP_OPENGL("glBindTexture(GL_TEXTURE2D, buffer=0)");
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer::setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data) {
        m_Channels = channels;
        m_Width = width;
        m_Height = height;

        GLenum dataFormat = _getDataFormat();
        int32_t internalFormat = _getInternalFormat();

        bind(0);

        GP_OPENGL("glTexImage2D(GL_TEXTURE_2D, width={0}, height={1}, channels={2})", width, height, channels);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                     (int32_t) m_Width, (int32_t) m_Height,
                     0, dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void TextureBuffer::setData(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height,
                                const uint8_t *data, uint32_t format) {
        bind(0);

        GP_OPENGL("glTexSubImage2D(width={0}, height={1}, xOffset={2}, yOffset={3})", width, height, xOffset, yOffset);
        glTexSubImage2D(GL_TEXTURE_2D, 0,
                        (int32_t) xOffset, (int32_t) yOffset,
                        (int32_t) width, (int32_t) height,
                        format, GL_UNSIGNED_BYTE, data);
    }

    void TextureBuffer::setData(uint32_t xOffset, uint32_t yOffset, const shared_ptr<gp::Bitmap> &bitmap) {
        setData(xOffset, yOffset, bitmap->getWidth(), bitmap->getHeight(), bitmap->getData(), bitmap->getDataFormat());
    }

    uint32_t TextureBuffer::_getDataFormat() const {
        switch (m_Channels) {
            case 4:
                return GL_RGBA;
            case 3:
                return GL_RGB;
            case 1:
                return GL_RED;
            default:
                GP_VALUE_ERROR("gp::Texture2D::_getDataFormat() invalid data format");
        }
        return -1;
    }

    int32_t TextureBuffer::_getInternalFormat() const {
        switch (m_Channels) {
            case 4:
                return GL_RGBA8;
            case 3:
                return GL_RGB8;
            case 1:
                return GL_R8;
            default:
                GP_VALUE_ERROR("gp::Texture2D::_getInternalFormat() invalid data format");
        }
        return -1;
    }

    int32_t TextureBuffer::getTextureSlots() {
        return s_TextureSlots;
    }
}
