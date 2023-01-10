#include "src/goopylib/texture/Texture2D.h"

#if GP_USING_OPENGL

#include <stb/stb_image.h>

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#if (GP_LOG_TEXTURE2D != true) and (GP_LOG_TEXTURE2D <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_TEXTURE2D
#endif

#if !GP_VALUE_CHECK_TEXTURE2D
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


namespace gp {
    Texture2D::Texture2D(const char *path) {
        GP_CORE_INFO("gp::Texture2D::Texture2D({0})", m_Path);

        uint8_t *data = stbi_load(path, (int32_t *) &m_Width, (int32_t *) &m_Height, (int32_t *) &m_Channels, 0);

        #if GP_ERROR_CHECKING
        if (m_Width == 0 and m_Height == 0 and m_Channels == 0) {
            GP_FILENOTFOUND_ERROR("gp::Texture2D::Texture2D() file '{0}' not found", path);
        }
        #endif

        GLenum dataFormat = _getDataFormat();
        int32_t internalFormat = _getInternalFormat();

        glGenTextures(1, &m_RendererID);
        bind(0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::Texture2D(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data)
            : m_Width(width),
              m_Height(height),
              m_Channels(channels) {
        GLenum dataFormat = _getDataFormat();
        int32_t internalFormat = _getInternalFormat();

        glGenTextures(1, &m_RendererID);
        bind(0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

    Texture2D::~Texture2D() {
        GP_CORE_DEBUG("gp::Texture2D::~Texture2D()");
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::init() {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_TextureSlots);
    }

    void Texture2D::bind(uint32_t slot) const {
        GP_CORE_TRACE_ALL("gp::Texture2D::bind({1}) - '{0}'", slot, m_Path);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture2D::unbind() {
        GP_CORE_WARN("gp::Texture2D::unbind()");
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::setData(const uint8_t *data, uint32_t width, uint32_t height, uint32_t channels) {
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

    void Texture2D::setData(const uint8_t *data, uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height) {
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

    uint32_t Texture2D::_getDataFormat() const {
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

    int32_t Texture2D::_getInternalFormat() const {
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
}

#endif
