#include "src/goopylib/Core/Texture2D.h"

namespace gp {
    Texture2D::Texture2D(const char *path)
            : m_Path(path) {
        GP_CORE_INFO("Initializing texture '{0}'", m_Path);

        m_Data = stbi_load(m_Path, &m_Width, &m_Height, &m_Channels, 0);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::init(uint32_t slot) {
        if (!m_Data) {
            m_Data = stbi_load(m_Path, &m_Width, &m_Height, &m_Channels, 0);
        }

        m_Slot = slot;
        GP_CORE_INFO("Loading texture '{0}' to slot {1}", m_Path, m_Slot);

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
        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_Data);

        stbi_image_free(m_Data);
        m_Data = nullptr;
    }

    void Texture2D::bind() const {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture2D::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
