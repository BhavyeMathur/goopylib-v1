#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "Texture2D.h"
#include "src/goopylib/maths/gpmath.h"
#include "src/goopylib/maths/packing/Shelf.h"

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
    class TextureAtlas {

        friend class Renderer;

    public:
        GPAPI TextureAtlas(const TextureAtlas &) = delete;

        GPAPI ~TextureAtlas();

        GPAPI TextureCoords add(const shared_ptr<Bitmap> &bitmap, bool allowRotation = true);

        GPAPI std::vector<TextureCoords> add(const std::vector<shared_ptr<Bitmap>> &bitmaps,
                                             bool allowRotation = true,
                                             const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        GPAPI static void init();

        [[nodiscard]] GPAPI static int32_t getWidth();

        [[nodiscard]] GPAPI static int32_t getHeight();

    private:
        packing::shelf::ShelfPackingAlgorithm *m_PackingAlgorithm;

        static std::vector<TextureAtlas *> s_Atlases;
        static int32_t s_Width;
        static int32_t s_Height;

        GPAPI TextureAtlas(packing::shelf::ShelfPackingAlgorithm *packingAlgorithm = nullptr);
    };
}
