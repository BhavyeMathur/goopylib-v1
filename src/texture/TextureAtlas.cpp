#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"
#include <opengl.h>


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;

    // TODO use TextureAtlas to optimise textures in the GPU
    TextureAtlas::TextureAtlas(packing::shelf::ShelfPackingAlgorithm packingAlgorithm)
            : m_PackingAlgorithm(packingAlgorithm) {
    }

    void TextureAtlas::init() {
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint *>(&s_Width));
        s_Height = s_Width;
    }

    uint32_t TextureAtlas::getWidth() {
        return s_Width;
    }

    uint32_t TextureAtlas::getHeight() {
        return s_Height;
    }

    std::vector<shared_ptr<packing::ShelvedBin>> TextureAtlas::getPages() {
        return m_PackingAlgorithm.bins();
    }

    TextureCoords TextureAtlas::add(const shared_ptr<Bitmap> &bitmap, bool allowRotation) {
        auto item = make_shared<packing::Item>(bitmap->getWidth(), bitmap->getHeight());
        m_PackingAlgorithm.pack(item, allowRotation);
        return {item->p1(), item->p2()};
    }

    std::vector<TextureCoords> TextureAtlas::add(const std::vector<shared_ptr<Bitmap>> &bitmaps, bool allowRotation,
                                                 const packing::SortingFunction &sorting) {
        std::vector<shared_ptr<packing::Item>> items;
        std::vector<TextureCoords> texCoords;
        items.reserve(bitmaps.size());
        texCoords.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps)
            items.emplace_back(new packing::Item(bitmap->getWidth(), bitmap->getHeight()));

        m_PackingAlgorithm.packAll(items, allowRotation, sorting);

        for (const auto &item: items)
            texCoords.emplace_back(item->p1(), item->p2());

        return texCoords;
    }
}
