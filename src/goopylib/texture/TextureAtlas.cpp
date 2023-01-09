#include "TextureAtlas.h"


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;
    std::vector<TextureAtlas *> TextureAtlas::s_Atlases;

    TextureAtlas::TextureAtlas()
    : m_Bin(nullptr) {
        s_Atlases.push_back(this);
    }

    TextureCoords TextureAtlas::add(const Bitmap &bitmap) {

    }
}
