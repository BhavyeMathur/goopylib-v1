#pragma once

#include "camera.h"

static PyTypeObject* Camera_pytype() {
    return &CameraType;
}
