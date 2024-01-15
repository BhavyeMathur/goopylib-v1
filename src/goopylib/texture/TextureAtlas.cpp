#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"


namespace gp {
    int32_t TextureAtlas::s_Width = 0;
    int32_t TextureAtlas::s_Height = 0;
    std::vector<TextureAtlas *> TextureAtlas::s_Atlases;
    
    // TODO use TextureAtlas to optimise textures in the GPU
    TextureAtlas::TextureAtlas(packing::shelf::ShelfPackingAlgorithm *packingAlgorithm)
            : m_PackingAlgorithm(packingAlgorithm) {
        s_Atlases.push_back(this);

        if (m_PackingAlgorithm == nullptr) {
            m_PackingAlgorithm = new packing::shelf::BestAreaFit((float) s_Width, (float) s_Height);
        }
    }

    TextureAtlas::~TextureAtlas() {
        // TODO replace with unique ptr
        delete m_PackingAlgorithm;
    }

    int32_t TextureAtlas::getWidth() {
        return s_Width;
    }

    int32_t TextureAtlas::getHeight() {
        return s_Height;
    }

    TextureCoords TextureAtlas::add(const shared_ptr<Bitmap> &bitmap, bool allowRotation) {
        auto item = shared_ptr<packing::Item>(new packing::Item((float) bitmap->getWidth(), (float) bitmap->getHeight()));
        m_PackingAlgorithm->pack(item, allowRotation);
        return {item->p1(), item->p2()};
    }

    std::vector<TextureCoords> TextureAtlas::add(const std::vector<shared_ptr<Bitmap>> &bitmaps,
                                                 bool allowRotation,
                                                 const packing::SortingFunction &sorting) {
        std::vector<shared_ptr<packing::Item>> items;
        std::vector<TextureCoords> texCoords;
        items.reserve(bitmaps.size());
        texCoords.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps) {
            items.emplace_back(new packing::Item((float) bitmap->getWidth(), (float) bitmap->getHeight()));
        }

        m_PackingAlgorithm->packAll(items, allowRotation, sorting);

        for (const auto &item: items) {
            texCoords.emplace_back(item->p1(), item->p2());
        }

        return texCoords;
    }
}
