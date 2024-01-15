#pragma once

#include "../quad/object.h"

namespace gp {
    class Rectangle;
}

struct RectangleObject {
    QuadObject base;
    shared_ptr<gp::Rectangle> rectangle;
};
