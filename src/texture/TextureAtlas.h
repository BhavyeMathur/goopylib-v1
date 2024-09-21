#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "TextureBuffer.h"

#include "maths/gpmath.h"
#include "maths/packing/algorithms/ScoredAlgorithms.h"

namespace gp {
    struct TextureCoords {
        Point p1;
        Point p2;

        TextureCoords(Point p1, Point p2)
                : p1(p1),
                  p2(p2) {
        }
    };
}

namespace gp {
    class GPAPI TextureAtlas {

    public:
        TextureAtlas(const TextureAtlas &) = delete;

        ~TextureAtlas() = default;

        TextureAtlas(packing::shelf::ShelfPackingAlgorithm packingAlgorithm = packing::shelf::BestAreaFit(s_Width, s_Height));

        TextureCoords add(const shared_ptr<Bitmap> &bitmap, bool allowRotation = true);

        std::vector<TextureCoords> add(const std::vector<shared_ptr<Bitmap>> &bitmaps,
                                       bool allowRotation = true,
                                       const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        static void init();

        [[nodiscard]] static uint32_t getWidth();

        [[nodiscard]] static uint32_t getHeight();

        [[nodiscard]] std::vector<shared_ptr<packing::ShelvedBin>> getPages();

    private:
        packing::shelf::ShelfPackingAlgorithm m_PackingAlgorithm;

        static uint32_t s_Width;
        static uint32_t s_Height;
    };
}
