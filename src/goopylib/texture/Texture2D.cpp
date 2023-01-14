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

    void Texture2D::setTextureType(TextureType value) {
        m_TextureType = value;
    }

    TextureType Texture2D::getTextureType() const {
        return m_TextureType;
    }
}
