#include "TextureCoords.h"

namespace gp {
    TextureCoords::TextureCoords(Point p1, Point p2)
            : p1(p1),
              p2(p2) {
    }

    Point TextureCoords::topleft() {
        return {p1.x, p2.y};
    }

    Point TextureCoords::topright() {
        return {p2.x, p2.y};
    }

    Point TextureCoords::bottomleft() {
        return {p1.x, p1.y};
    }

    Point TextureCoords::bottomright() {
        return {p2.x, p1.y};
    }

    TextureAtlasCoords::TextureAtlasCoords(Point p1, Point p2, uint32_t page)
            : coords({p1, p2}),
              page(page) {
    }
}
