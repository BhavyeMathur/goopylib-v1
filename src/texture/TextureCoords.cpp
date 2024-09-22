#include "TextureCoords.h"

namespace gp {
    TextureCoords::TextureCoords(Point p1, Point p2)
            : p1(p1),
              p2(p2) {
    }

    TextureAtlasCoords::TextureAtlasCoords(Point p1, Point p2, uint32_t page)
            : coords({p1, p2}),
              page(page) {
    }
}
