#include "src/goopylib/Core/Texture2D.h"

#include <stb/stb_image.h>

#if GP_USING_OPENGL

#include <OpenGL/gl.h>

#endif

namespace gp {
    Texture2D::Texture2D(const char *path)
            : m_Path(path) {
        GP_CORE_INFO("Initializing texture '{0}'", m_Path);

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
            GP_CORE_ERROR("Unsupported Image Format");
            internalFormat = 0;
            dataFormat = 0;
        }

        glGenTextures(1, &m_RendererID);
        bind(0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::bind(uint32_t slot) const {
        GP_CORE_TRACE_ALL("Binding 2D Texture {0} to {1}", m_Path, slot);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture2D::unbind() {
        GP_CORE_WARN("Unbinding 2D Textures");
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
