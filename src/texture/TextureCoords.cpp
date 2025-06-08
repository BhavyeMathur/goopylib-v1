#include "TextureCoords.h"

namespace gp {
    TextureCoords::TextureCoords(Point p1, Point p2)
            : p1(p1),
              p2(p2) {
    }

    Point TextureCoords::topleft() const {
        return {p1.x, p2.y};
    }

    Point TextureCoords::topright() const {
        return {p2.x, p2.y};
    }

    Point TextureCoords::bottomleft() const {
        return {p1.x, p1.y};
    }

    Point TextureCoords::bottomright() const {
        return {p2.x, p1.y};
    }

    TextureAtlasCoords::TextureAtlasCoords(Point p1, Point p2, uint32_t page)
            : coords({p1, p2}),
              page(page) {
    }
}
