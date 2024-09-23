#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "TextureBuffer.h"

#include "maths/gpmath.h"
#include "maths/packing/algorithms/ScoredAlgorithms.h"

namespace gp {
    struct TextureAtlasCoords;

    class GPAPI TextureAtlas {

    public:
        TextureAtlas(const TextureAtlas &) = delete;

        TextureAtlas(uint32_t channels, unique_ptr<packing::shelf::ShelfPackingAlgorithm> packingAlgorithm = nullptr);

        TextureAtlasCoords add(const shared_ptr<Bitmap> &bitmap, bool allowRotation = true);

        std::vector<TextureAtlasCoords> add(const std::vector<shared_ptr<Bitmap>> &bitmaps, bool allowRotation = true,
                                            const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        static void init();

        [[nodiscard]] static uint32_t width();

        [[nodiscard]] static uint32_t height();

        [[nodiscard]] uint32_t pages();

        [[nodiscard]] const shared_ptr<Bitmap> &getBitmap(uint32_t i) const;

        [[nodiscard]] TextureAtlasCoords toUVCoordinate(Point x, Point y, uint32_t page);

    private:
        unique_ptr<packing::shelf::ShelfPackingAlgorithm> m_PackingAlgorithm;
        std::vector<shared_ptr<Bitmap>> m_Bitmaps;

        const uint32_t m_Channels;

        static uint32_t s_Width;
        static uint32_t s_Height;
    };
}
