#pragma once

#include "gp.h"
#include "goopylib/header.h"

namespace gp {
    class Renderable;
}

struct RenderableObject {
    PyObject_HEAD
    Ref<gp::Renderable> renderable;
};
