#pragma once

#include "gp.h"
#include "goopylib/header.h"

namespace gp {
    class Renderable;
}

struct RenderableObject {
    PyObject_HEAD
    shared_ptr<gp::Renderable> renderable;
};
