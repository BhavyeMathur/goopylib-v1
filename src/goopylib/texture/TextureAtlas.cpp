#include "TextureAtlas.h"


namespace gp {
    int32_t TextureAtlas::s_Width = 0;
    int32_t TextureAtlas::s_Height = 0;
    std::vector<TextureAtlas *> TextureAtlas::s_Atlases;

    TextureAtlas::TextureAtlas(packing::shelf::ShelfPackingAlgorithm *packingAlgorithm)
            : m_PackingAlgorithm(packingAlgorithm) {
        s_Atlases.push_back(this);

        if (m_PackingAlgorithm == nullptr) {
            m_PackingAlgorithm = new packing::shelf::BestAreaFit((float) s_Width, (float) s_Height);
        }
    }

    TextureAtlas::~TextureAtlas() {
        delete m_PackingAlgorithm;
    }

    int32_t TextureAtlas::getWidth() {
        return s_Width;
    }

    int32_t TextureAtlas::getHeight() {
        return s_Height;
    }

    TextureCoords TextureAtlas::add(const Ref<Bitmap> &bitmap, bool allowRotation) {
        auto item = Ref<packing::Item>(new packing::Item((float) bitmap->getWidth(), (float) bitmap->getHeight()));
        m_PackingAlgorithm->pack(item, allowRotation);
        return {item->p1(), item->p2()};
    }

    std::vector<TextureCoords> TextureAtlas::add(const std::vector<Ref<Bitmap>> &bitmaps,
                                                 bool allowRotation,
                                                 const packing::SortingFunction &sorting) {
        std::vector<Ref<packing::Item>> items;
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

    std::vector<Texture2D> TextureAtlas::createTextureAtlas() const {
        std::vector<Texture2D> textures;
        textures.reserve(m_PackingAlgorithm->bins().size());

        for (const auto &bin: m_PackingAlgorithm->bins()) {
            int32_t width = 0;
            int32_t height = 0;

            for (const auto &shelf: *bin) {
                if ((int32_t) shelf->getWidth() > width) {
                    width = (int32_t) shelf->getWidth();
                }
                height += (int32_t) shelf->getHeight();
            }

            auto texture = Texture2D(width, height, 1);

            for (const auto &item: bin->items()) {
                texture.setData((uint32_t) item->getX(),
                                (uint32_t) item->getY(),
                                (uint32_t) item->getWidth(),
                                (uint32_t) item->getHeight(),
                                nullptr);
            }

            textures.push_back(texture);
        }

        return textures;
    }
}
