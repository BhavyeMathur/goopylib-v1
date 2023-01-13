#include "TextureAtlas.h"
#include "Texture2D.h"
#include "Bitmap.h"


#if (GP_LOG_TEXTURE_ATLAS != true) and (GP_LOG_TEXTURE_ATLAS <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_TEXTURE_ATLAS
#endif

#if !GP_VALUE_CHECK_TEXTURE_ATLAS
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;

    TextureAtlas::TextureAtlas(uint32_t channels, packing::shelf::ShelfPackingAlgorithm *packingAlgorithm)
            : m_PackingAlgorithm(packingAlgorithm),
              m_Channels(channels) {
        GP_CORE_INFO("gp::TextureAtlas::TextureAtlas(channels={0})", channels);
        if (m_PackingAlgorithm == nullptr) {
            m_PackingAlgorithm = new packing::shelf::BestAreaFit((float) s_Width, (float) s_Height);
        }
    }

    TextureAtlas::~TextureAtlas() {
        GP_CORE_INFO("gp::TextureAtlas::~TextureAtlas()");
        delete m_PackingAlgorithm;
    }

    uint32_t TextureAtlas::getChannels() const {
        return m_Channels;
    }

    uint32_t TextureAtlas::getPages() const {
        return m_PackingAlgorithm->getPages();
    }

    Ref<Texture2D> TextureAtlas::getTextureAt(uint32_t index) const {
        return m_Textures[index];
    }

    uint32_t TextureAtlas::getWidth() {
        return s_Width;
    }

    uint32_t TextureAtlas::getHeight() {
        return s_Height;
    }

    TextureCoords TextureAtlas::add(const Ref<Bitmap> &bitmap, bool allowRotation) {
        m_Bitmaps.push_back(bitmap);
        auto item = Ref<packing::Item>(
                new packing::Item((float) bitmap->getWidth(), (float) bitmap->getHeight(), (void *) bitmap->getData()));

        m_PackingAlgorithm->pack(item, allowRotation);
        while (m_Textures.size() < m_PackingAlgorithm->getPages()) {
            m_Textures.push_back(Ref<Texture2D>(new Texture2D(0, 0, m_Channels)));
        }

        return {item->p1(), item->p2(), item->getPage(), m_Textures[item->getPage()]};
    }

    std::vector<TextureCoords> TextureAtlas::add(const std::vector<Ref<Bitmap>> &bitmaps,
                                                 bool allowRotation,
                                                 const packing::SortingFunction &sorting) {
        std::vector<Ref<packing::Item>> items;
        std::vector<TextureCoords> texCoords;
        items.reserve(bitmaps.size());
        texCoords.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps) {
            m_Bitmaps.push_back(bitmap);
            items.emplace_back(
                    new packing::Item((float) bitmap->getWidth(),
                                      (float) bitmap->getHeight(),
                                      (void *) bitmap->getData()));
        }

        m_PackingAlgorithm->packAll(items, allowRotation, sorting);
        while (m_Textures.size() < m_PackingAlgorithm->getPages()) {
            m_Textures.push_back(Ref<Texture2D>(new Texture2D(0, 0, m_Channels)));
        }

        for (const auto &item: items) {
            texCoords.emplace_back(item->p1(), item->p2(), item->getPage(), m_Textures[item->getPage()]);
        }

        return texCoords;
    }

    void TextureAtlas::createTextureAtlas() const {

        uint32_t i = 0;
        for (const auto &bin: m_PackingAlgorithm->bins()) {
            uint32_t width = 0;
            uint32_t height = 0;

            for (const auto &shelf: *bin) {
                if ((uint32_t) shelf->getPackedWidth() > width) {
                    width = (uint32_t) shelf->getPackedWidth();
                }
                height += (uint32_t) shelf->getHeight();
            }

            if (height == 0) {
                continue;
            }

            auto texture = m_Textures[i];
            texture->setData(width, height, m_Channels);

            for (const auto &item: bin->items()) {
                texture->setData((uint32_t) item->getX(),
                                 (uint32_t) item->getY(),
                                 (uint32_t) item->getWidth(),
                                 (uint32_t) item->getHeight(),
                                 (uint8_t *) item->getUserObject());
            }
            i++;
        }
    }
}
