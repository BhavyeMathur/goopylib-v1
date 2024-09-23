#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"
#include "TextureCoords.h"
#include "maths/packing/Item.h"
#include <opengl.h>


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;

    // TODO use TextureAtlas to optimise textures in the GPU
    TextureAtlas::TextureAtlas(uint32_t channels, unique_ptr<packing::shelf::ShelfPackingAlgorithm> packingAlgorithm)
            : m_PackingAlgorithm(std::move(packingAlgorithm)),
              m_Channels(channels) {
        if (packingAlgorithm == nullptr)
            m_PackingAlgorithm = make_unique<packing::shelf::BestAreaFit>(s_Width, s_Height);
    }

    void TextureAtlas::init() {
        // glGetIntegerv(GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint *>(&s_Width));
        s_Width = 64;
        s_Height = s_Width;
    }

    uint32_t TextureAtlas::width() {
        return s_Width;
    }

    uint32_t TextureAtlas::height() {
        return s_Height;
    }

    uint32_t TextureAtlas::pages() {
        return m_PackingAlgorithm->pages();
    }

    const shared_ptr<Bitmap> &TextureAtlas::getBitmap(uint32_t i) const {
        return m_Bitmaps.at(i);
    }

    TextureAtlasCoords TextureAtlas::add(const shared_ptr<Bitmap> &bitmap, bool allowRotation) {
        auto item = packing::Item(bitmap->getWidth(), bitmap->getHeight());
        m_PackingAlgorithm->pack(item, allowRotation);

        while (m_PackingAlgorithm->pages() > m_Bitmaps.size())
            m_Bitmaps.push_back(make_unique<Bitmap>(s_Width, s_Height, m_Channels));
        m_Bitmaps[item.page()]->setSubdata(*bitmap, item.p1().x, item.p1().y);

        return {item.p1(), item.p2(), item.page()};
    }

    std::vector<TextureAtlasCoords> TextureAtlas::add(const std::vector<shared_ptr<Bitmap>> &bitmaps,
                                                      bool allowRotation, const packing::SortingFunction &sorting) {
        std::vector<packing::Item> items;
        std::vector<TextureAtlasCoords> texCoords;
        items.reserve(bitmaps.size());
        texCoords.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps)
            items.emplace_back(bitmap->getWidth(), bitmap->getHeight());

        m_PackingAlgorithm->packAll(items, allowRotation, sorting);

        while (m_PackingAlgorithm->pages() > m_Bitmaps.size())
            m_Bitmaps.push_back(make_unique<Bitmap>(s_Width, s_Height, m_Channels));

        for (int32_t i = 0; i < items.size(); i++) {
            const auto &item = items[i];
            const auto &bitmap = bitmaps[i];

            texCoords.emplace_back(item.p1(), item.p2(), item.page());
            m_Bitmaps[item.page()]->setSubdata(*bitmap, item.p1().x, item.p1().y);
        }

        return texCoords;
    }
}
