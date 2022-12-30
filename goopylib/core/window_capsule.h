#pragma once

#include "window.h"

static PyTypeObject* Window_pytype() {
    return &WindowType;
}
