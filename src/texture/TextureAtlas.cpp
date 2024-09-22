#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"
#include "TextureCoords.h"
#include "maths/packing/Item.h"
#include <opengl.h>


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;

    // TODO use TextureAtlas to optimise textures in the GPU
    TextureAtlas::TextureAtlas(packing::shelf::ShelfPackingAlgorithm packingAlgorithm)
            : m_PackingAlgorithm(packingAlgorithm),
              m_Channels(3) {
    }

    void TextureAtlas::init() {
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint *>(&s_Width));
        s_Height = s_Width;
    }

    uint32_t TextureAtlas::width() {
        return s_Width;
    }

    uint32_t TextureAtlas::height() {
        return s_Height;
    }

    const std::vector<packing::ShelvedBin> &TextureAtlas::getPages() const {
        return m_PackingAlgorithm.bins();
    }

    TextureCoords TextureAtlas::add(const shared_ptr<Bitmap> &bitmap, bool allowRotation) {
        auto item = packing::Item(bitmap->getWidth(), bitmap->getHeight());
        m_PackingAlgorithm.pack(item, allowRotation);

        while (item.page() >= m_Bitmaps.size())
            m_Bitmaps.emplace_back(s_Width, s_Height, m_Channels);
        m_Bitmaps[item.page()];

        return {item.p1(), item.p2()};
    }

    std::vector<TextureCoords> TextureAtlas::add(const std::vector<shared_ptr<Bitmap>> &bitmaps, bool allowRotation,
                                                 const packing::SortingFunction &sorting) {
        std::vector<packing::Item> items;
        std::vector<TextureCoords> texCoords;
        items.reserve(bitmaps.size());
        texCoords.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps)
            items.emplace_back(bitmap->getWidth(), bitmap->getHeight());

        m_PackingAlgorithm.packAll(items, allowRotation, sorting);

        for (const auto &item: items)
            texCoords.emplace_back(item.p1(), item.p2());

        return texCoords;
    }
}
