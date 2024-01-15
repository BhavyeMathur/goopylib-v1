#pragma once

#include "../rectangle/object.h"

namespace gp {
    class Image;
}

struct ImageObject {
    RectangleObject base;
    shared_ptr<gp::Image> image;
};
