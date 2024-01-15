#pragma once

#include "../quad/object.h"

namespace gp {
    class Line;
}

struct LineObject {
    QuadObject base;
    shared_ptr<gp::Line> line;
};
