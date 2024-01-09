#pragma once

#include "../rectangle/object.h"

namespace gp {
    class Image;
}

struct ImageObject {
    RectangleObject base;
    Ref<gp::Image> image;
};
