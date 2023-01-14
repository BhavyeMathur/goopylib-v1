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

        m_TextureType = getTextureTypeFromChannels(m_Channels);
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

    void TextureAtlas::setTextureType(TextureType value) {
        m_TextureType = value;
    }

    TextureType TextureAtlas::getTextureType() const {
        return m_TextureType;
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
                new packing::Item((float) bitmap->getWidth(), (float) bitmap->getHeight(), (void *) bitmap.get()));

        m_PackingAlgorithm->pack(item, allowRotation);
        while (m_Textures.size() < m_PackingAlgorithm->getPages()) {
            auto texture = new Texture2D(0, 0, m_Channels);
            texture->setTextureType(m_TextureType);
            m_Textures.push_back(Ref<Texture2D>(texture));
        }
        return {item->p1(), item->p2(), item->getPage(), item->isRotated(), m_Textures[item->getPage()]};
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
                                      (void *) bitmap.get()));
        }

        m_PackingAlgorithm->packAll(items, allowRotation, sorting);
        while (m_Textures.size() < m_PackingAlgorithm->getPages()) {
            auto texture = new Texture2D(0, 0, m_Channels);
            texture->setTextureType(m_TextureType);
            m_Textures.push_back(Ref<Texture2D>(texture));
        }

        for (const auto &item: items) {
            texCoords.emplace_back(item->p1(),
                                   item->p2(),
                                   item->getPage(),
                                   item->isRotated(),
                                   m_Textures[item->getPage()]);
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
            texture->setData(width, height);

            for (const auto &item: bin->items()) {
                auto bitmap = ((Bitmap *) item->getUserObject());
                auto bitmapWidth = (uint32_t) item->getWidth();
                auto bitmapHeight = (uint32_t) item->getHeight();
                uint8_t *data = bitmap->getData();

                if (item->isRotated()) {
                    auto *transposedData = new uint8_t[m_Channels * bitmapWidth * bitmapHeight];

                    uint32_t index = 0;
                    for (uint32_t y = 0; y < bitmapWidth; y++) {
                        for (uint32_t x = 0; x < bitmapHeight; x++) {
                            for (uint32_t z = 0; z < m_Channels; z++) {
                                transposedData[m_Channels * (x * bitmapWidth + y) + z] = data[index++];
                            }
                        }
                    }

                    data = transposedData;
                }

                texture->setData((uint32_t) item->getX(), (uint32_t) item->getY(),
                                 bitmapWidth, bitmapHeight, data);
            }
            i++;
        }
    }
}
