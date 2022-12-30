#pragma once

#include "header.h"
#include "goopylib/scene/Camera.h"

struct CameraObject {
    PyObject_HEAD
    Ref<gp::Camera> camera;
};
