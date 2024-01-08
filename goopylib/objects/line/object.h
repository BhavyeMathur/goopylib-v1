#pragma once

#include "../quad/object.h"

namespace gp {
    class Line;
}

struct LineObject {
    QuadObject base;
    Ref<gp::Line> line;
};
