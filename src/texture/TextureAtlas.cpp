#define GP_LOGGING_LEVEL 3

#include "TextureAtlas.h"
#include "TextureCoords.h"
#include "maths/packing/Item.h"

#include "debug/Error.h"

#include <opengl.h>
#include <GLFW/glfw3.h>


namespace gp {
    uint32_t TextureAtlas::s_MaxWidth = 0;
    uint32_t TextureAtlas::s_MaxHeight = 0;

    TextureAtlas::TextureAtlas(uint32_t channels, unique_ptr<packing::ShelfPackingAlgorithm> packingAlgorithm)
            : TextureAtlas(1024, 1024, channels, std::move(packingAlgorithm)) {
    }

    TextureAtlas::TextureAtlas(uint32_t width, uint32_t height, uint32_t channels,
                               unique_ptr<packing::ShelfPackingAlgorithm> packingAlgorithm)
            : m_PackingAlgorithm(std::move(packingAlgorithm)),
              m_Width(width),
              m_Height(height),
              m_Channels(channels) {
        GP_CHECK_LE(width, s_MaxWidth, strformat("gp::TextureAtlas::TextureAtlas() max width is %i", s_MaxWidth));
        GP_CHECK_LE(height, s_MaxHeight, strformat("gp::TextureAtlas::TextureAtlas() max height is %i", s_MaxHeight));

        if (packingAlgorithm == nullptr)
            m_PackingAlgorithm = make_unique<packing::BestAreaFit>(s_MaxWidth, s_MaxHeight);
    }

    void TextureAtlas::init() {
        GP_CHECK_ACTIVE_CONTEXT("gp::TextureAtlas::init()");

        GP_OPENGL("glGetIntegerv(GL_MAX_TEXTURE_SIZE");
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint *>(&s_MaxWidth));
        s_MaxHeight = s_MaxWidth;
    }

    uint32_t TextureAtlas::width() {
        return m_Width;
    }

    uint32_t TextureAtlas::height() {
        return m_Height;
    }

    uint32_t TextureAtlas::pages() {
        return m_PackingAlgorithm->pages();
    }

    bool TextureAtlas::contains(const std::string &texture) const {
        return m_TextureData.contains(texture);
    }

    const TextureData &TextureAtlas::getTextureData(const std::string &texture) const {
        return m_TextureData.at(texture);
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
            items.emplace_back(bitmap->width(), bitmap->height());

        m_PackingAlgorithm->pack(items, allowRotation, sorting);
        _createTextureBuffers();

        for (int32_t i = 0; i < items.size(); i++) {
            const auto &item = items[i];
            auto &bitmap = bitmaps[i];

            m_TextureBuffers[item.page()]->setData(item.p1().x, item.p1().y, bitmap);
            m_TextureData.insert({bitmap->name(), {item.page(), toUVCoordinate(item.p1(), item.p2())}});
        }
    }

    TextureCoords TextureAtlas::toUVCoordinate(Point p1, Point p2) {
        // see https://gamedev.stackexchange.com/questions/46963/how-to-avoid-texture-bleeding-in-a-texture-atlas
        // for why we add/subtract 0.5
        return {(p1 + 0.5) / m_Width, (p2 - 0.5) / m_Height};
    }

    void TextureAtlas::_createTextureBuffers() {
        while (m_TextureBuffers.size() < pages())
            m_TextureBuffers.push_back(make_shared<TextureBuffer>(m_Width, m_Height, m_Channels));
    }
}
