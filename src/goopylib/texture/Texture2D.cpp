#include "Texture2D.h"
#include "TextureType.h"

namespace gp {
    int32_t Texture2D::s_TextureSlots = 0;

    int32_t Texture2D::getTextureSlots() {
        return s_TextureSlots;
    }

    uint32_t Texture2D::getWidth() const {
        return m_Width;
    }

    uint32_t Texture2D::getHeight() const {
        return m_Height;
    }

    uint32_t Texture2D::getChannels() const {
        return m_Channels;
    }

    TextureType Texture2D::getTextureType() const {
        return m_TextureType;
    }

    void Texture2D::_setTextureType() {
        switch (m_Channels) {
            case 1:
                m_TextureType = TextureType::Greyscale;

            case 3:
                m_TextureType = TextureType::RGB;

            case 4:
                m_TextureType = TextureType::RGBA;
        }
    }
}
