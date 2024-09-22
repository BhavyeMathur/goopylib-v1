#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "TextureBuffer.h"

#include "maths/gpmath.h"
#include "maths/packing/algorithms/ScoredAlgorithms.h"

namespace gp {
    struct TextureCoords;

    class GPAPI TextureAtlas {

    public:
        TextureAtlas(const TextureAtlas &) = delete;

        TextureAtlas(packing::shelf::ShelfPackingAlgorithm packingAlgorithm = packing::shelf::BestAreaFit(s_Width,
                                                                                                          s_Height));

        TextureCoords add(const shared_ptr<Bitmap> &bitmap, bool allowRotation = true);

        std::vector<TextureCoords> add(const std::vector<shared_ptr<Bitmap>> &bitmaps, bool allowRotation = true,
                                       const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        static void init();

        [[nodiscard]] static uint32_t width();

        [[nodiscard]] static uint32_t height();

        [[nodiscard]] const std::vector<packing::ShelvedBin> &getPages() const;

    private:
        packing::shelf::ShelfPackingAlgorithm m_PackingAlgorithm;
        std::vector<Bitmap> m_Bitmaps;

        const uint32_t m_Channels;

        static uint32_t s_Width;
        static uint32_t s_Height;
    };
}
