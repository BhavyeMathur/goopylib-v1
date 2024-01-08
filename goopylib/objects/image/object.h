#pragma once

#include "../renderable/object.h"

namespace gp {
    class Image;
}

struct ImageObject {
    RenderableObject base;
    Ref<gp::Image> image;
};
