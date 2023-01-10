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

        friend class Image;

        friend class Text;

    public:
        GPAPI TextureCoords add(const Ref<Bitmap> &bitmap, bool allowRotation = true);

        GPAPI std::vector<TextureCoords> add(const std::vector<Ref<Bitmap>> &bitmaps,
                                             bool allowRotation = true,
                                             const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        GPAPI std::vector<Texture2D> createTextureAtlas() const;

        GPAPI static void init();

    private:
        packing::shelf::ShelfPackingAlgorithm *m_PackingAlgorithm;

        static std::vector<TextureAtlas *> s_Atlases;
        static uint32_t s_Width;
        static uint32_t s_Height;

        TextureAtlas(packing::shelf::ShelfPackingAlgorithm *packingAlgorithm = nullptr);

        ~TextureAtlas();
    };
}
