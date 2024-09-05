#define GP_LOGGING_LEVEL 3

#include "TextureBuffer.h"
#include "Bitmap.h"
#include "debug/Error.h"

#include <opengl.h>


namespace gp {
    int32_t TextureBuffer::s_TextureSlots = 0;

    TextureBuffer::TextureBuffer(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data)
        : m_Width(width),
          m_Height(height),
          m_Channels(channels) {
        GLenum dataFormat = _getDataFormat();
        int32_t internalFormat = _getInternalFormat();

        glGenTextures(1, &m_RendererID);
        bind(0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         internalFormat,
                         (int32_t) m_Width,
                         (int32_t) m_Height,
                         0, dataFormat,
                         GL_UNSIGNED_BYTE,
                         data);
        }
    }

    TextureBuffer::TextureBuffer(const Bitmap &bitmap)
        : TextureBuffer(bitmap.getWidth(), bitmap.getHeight(), bitmap.getChannels(), bitmap.getData()) {
    }

    TextureBuffer::~TextureBuffer() {
        GP_CORE_DEBUG("gp::Texture2D::~Texture2D()");
        glDeleteTextures(1, &m_RendererID);
    }

    void TextureBuffer::init() {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_TextureSlots);
    }

    void TextureBuffer::bind(uint32_t slot) const {
        GP_CORE_TRACE_ALL("gp::Texture2D::bind({1}) - '{0}'", slot, m_Path);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void TextureBuffer::unbind() {
        GP_CORE_WARN("gp::Texture2D::unbind()");
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer::setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data) {
        m_Channels = channels;
        m_Width = width;
        m_Height = height;

        GLenum dataFormat = _getDataFormat();
        int32_t internalFormat = _getInternalFormat();

        bind(0);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     internalFormat,
                     (int32_t) m_Width,
                     (int32_t) m_Height,
                     0, dataFormat,
                     GL_UNSIGNED_BYTE,
                     data);
    }

    void TextureBuffer::setData(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, const uint8_t *data) {
        int32_t internalFormat = _getInternalFormat();

        bind(0);
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        (int32_t) xOffset,
                        (int32_t) yOffset,
                        (int32_t) width,
                        (int32_t) height,
                        internalFormat,
                        GL_UNSIGNED_BYTE,
                        data);
    }

    uint32_t TextureBuffer::_getDataFormat() const {
        if (m_Channels == 4) {
            return GL_RGBA;
        }
        else if (m_Channels == 3) {
            return GL_RGB;
        }
        else if (m_Channels == 1) {
            return GL_RED;
        }
        else {
            GP_VALUE_ERROR("gp::Texture2D::_getDataFormat() invalid data format");
        }
        return 0;
    }

    int32_t TextureBuffer::_getInternalFormat() const {
        if (m_Channels == 4) {
            return GL_RGBA8;
        }
        else if (m_Channels == 3) {
            return GL_RGB8;
        }
        else if (m_Channels == 1) {
            return GL_R8;
        }
        else {
            GP_VALUE_ERROR("gp::Texture2D::_getInternalFormat() invalid data format");
        }
        return 0;
    }

    int32_t TextureBuffer::getTextureSlots() {
        return s_TextureSlots;
    }
}
