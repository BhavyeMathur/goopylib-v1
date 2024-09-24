#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"
#include "TextureCoords.h"
#include "maths/packing/Item.h"

#include "debug/Error.h"

#include <opengl.h>
#include <GLFW/glfw3.h>


namespace gp {
    uint32_t TextureAtlas::s_Width = 0;
    uint32_t TextureAtlas::s_Height = 0;

    TextureAtlas::TextureAtlas(uint32_t channels, unique_ptr<packing::ShelfPackingAlgorithm> packingAlgorithm)
            : m_PackingAlgorithm(std::move(packingAlgorithm)),
              m_Channels(channels) {
        if (packingAlgorithm == nullptr)
            m_PackingAlgorithm = make_unique<packing::BestAreaFit>(s_Width, s_Height);
    }

    void TextureAtlas::init() {
        GP_CHECK_ACTIVE_CONTEXT("gp::TextureAtlas::init()");

        // GP_OPENGL("glGetIntegerv(GL_MAX_TEXTURE_SIZE");
        // glGetIntegerv(GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint *>(&s_Width));

        // TODO TextureAtlas should dynamically adjust its width to ensure we are not copying more data than required
        s_Width = 128;
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

    bool TextureAtlas::contains(const std::string &texture) const {
        return m_TexturesCache.contains(texture);
    }

    const TextureData &TextureAtlas::getTextureData(const std::string &texture) const {
        return m_TexturesCache.at(texture);
    }

    const shared_ptr<Bitmap> &TextureAtlas::getBitmap(uint32_t i) const {
        return m_Bitmaps.at(i);
    }

    const shared_ptr<TextureBuffer> &TextureAtlas::getTextureBuffer(uint32_t i) const {
        return m_TextureBuffers.at(i);
    }

    void TextureAtlas::add(const shared_ptr<Bitmap> &bitmap, bool allowRotation) {
        add({bitmap}, allowRotation, nullptr);
    }

    void TextureAtlas::add(const std::vector<shared_ptr<Bitmap>> &bitmaps,
                                                      bool allowRotation, const packing::SortingFunction &sorting) {
        std::vector<packing::Item> items;
        items.reserve(bitmaps.size());

        for (const auto &bitmap: bitmaps)
            items.emplace_back(bitmap->getWidth(), bitmap->getHeight());

        m_PackingAlgorithm->packAll(items, allowRotation, sorting);

        while (m_PackingAlgorithm->pages() > m_Bitmaps.size())
            m_Bitmaps.push_back(make_unique<Bitmap>(s_Width, s_Height, m_Channels));

        _updateTextureBufferData();

        for (int32_t i = 0; i < items.size(); i++) {
            const auto &item = items[i];
            auto texCoord = toUVCoordinate(item.p1(), item.p2(), item.page());
            auto &bitmap = bitmaps[i];

            // TODO TextureAtlas should directly set the subdata of the TextureBuffer, this is slower
            m_Bitmaps[item.page()]->setSubdata(*bitmap, item.p1().x, item.p1().y);
            m_TextureBuffers[item.page()]->setData(item.p1().x, item.p1().y, bitmap);
            m_TexturesCache.insert({bitmap->name(), {item.page(), texCoord.coords}});
        }
    }

    TextureAtlasCoords TextureAtlas::toUVCoordinate(Point p1, Point p2, uint32_t page) {
        // see https://gamedev.stackexchange.com/questions/46963/how-to-avoid-texture-bleeding-in-a-texture-atlas
        // for why we add/subtract 0.5
        return {(p1 + 0.5) / s_Width, (p2 - 0.5) / s_Width, page};
    }

    void TextureAtlas::_updateTextureBufferData() {
        uint32_t i = m_TextureBuffers.size();
        while (i < pages()) {
            getBitmap(i)->saveBitmap(strformat("%i.png", i));
            m_TextureBuffers.push_back(make_shared<TextureBuffer>(*getBitmap(i)));
            i++;
        }
    }
}
