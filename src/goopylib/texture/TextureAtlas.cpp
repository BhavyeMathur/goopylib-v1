#include "TextureAtlas.h"


namespace gp {
    static uint32_t s_Width = 0;
    static uint32_t s_Height = 0;

    TextureAtlas::TextureAtlas()
    : m_Bin(nullptr) {
        s_Atlases.push_back(this);
    }

    TextureCoords TextureAtlas::add(const Bitmap &bitmap) {

    }
}
