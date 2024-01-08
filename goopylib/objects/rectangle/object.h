#pragma once

#include "../quad/object.h"

namespace gp {
    class Rectangle;
}

struct RectangleObject {
    QuadObject base;
    Ref<gp::Rectangle> rectangle;
};
