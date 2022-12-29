#include "goopylib/core/Texture2D.h"

#include <stb/stb_image.h>

#if GP_USING_OPENGL

#include <OpenGL/gl.h>

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

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


namespace gp {
    Texture2D::Texture2D(const char *path)
            : m_Path(path) {
        GP_CORE_INFO("gp::Texture2D::Texture2D({0})", m_Path);

        u_char *data = stbi_load(m_Path, &m_Width, &m_Height, &m_Channels, 0);

        GLenum dataFormat;
        int32_t internalFormat;

        if (m_Channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (m_Channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else {
            if (m_Width == 0 and m_Height == 0 and m_Channels == 0) {
                GP_FILENOTFOUND_ERROR("File '{0}' not found", m_Path);
            }
            else {
                GP_VALUE_ERROR("Unsupported image format '{0}'", m_Path);
            }

            internalFormat = 0;
            dataFormat = 0;
        }

        glGenTextures(1, &m_RendererID);
        bind(0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {
        GP_CORE_DEBUG("gp::Texture2D::~Texture2D()");
        glDeleteTextures(1, &m_RendererID);
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
}
