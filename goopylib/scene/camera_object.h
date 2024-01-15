#pragma once

#include "goopylib/header.h"
#include "src/goopylib/scene/Camera.h"

struct CameraObject {
    PyObject_HEAD
    shared_ptr<gp::Camera> camera;
};
