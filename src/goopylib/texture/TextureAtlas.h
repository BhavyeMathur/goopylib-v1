#pragma once

#include <utility>

#include "gp.h"
#include "src/goopylib/maths/packing/Shelf.h"

namespace gp {
    class Texture2D;

    struct TextureCoords {
        Point p1;
        Point p2;
        uint32_t page = 0;

        Ref<Texture2D> texture;

        TextureCoords() = default;

        TextureCoords(Point p1, Point p2, uint32_t page, Ref<Texture2D> texture)
                : p1(p1),
                  p2(p2),
                  page(page),
                  texture(std::move(texture)) {
        }
    };
}

namespace gp {
    class Bitmap;

    class TextureAtlas {

        friend class Renderer;

    public:
        GPAPI ~TextureAtlas();

        GPAPI TextureCoords add(const Ref<Bitmap> &bitmap, bool allowRotation = true);

        GPAPI std::vector<TextureCoords> add(const std::vector<Bitmap *> &bitmaps,
                                             bool allowRotation = true,
                                             const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        GPAPI void createTextureAtlas() const;

        GPAPI uint32_t getChannels() const;

        GPAPI uint32_t getPages() const;

        GPAPI Ref<Texture2D> getTextureAt(uint32_t index) const;

        GPAPI static void init();

        GPAPI static uint32_t getWidth();

        GPAPI static uint32_t getHeight();

    private:
        packing::shelf::ShelfPackingAlgorithm *m_PackingAlgorithm = nullptr;
        std::vector<Ref<Texture2D>> m_Textures;
        std::vector<Ref<Bitmap>> m_Bitmaps;

        uint32_t m_Channels = 0;
        static uint32_t s_Width;
        static uint32_t s_Height;

        TextureAtlas() = default;

        TextureAtlas(uint32_t channels, packing::shelf::ShelfPackingAlgorithm *packingAlgorithm = nullptr);
    };
}
