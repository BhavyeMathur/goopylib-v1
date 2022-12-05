#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "goopylib/Math/gpmath.h"

#ifdef __APPLE__
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#define UNSUPPORTED_PLATFORM_ERROR #error Unsupported Platform
#define GP_USING_GLFW true
#define GP_USING_OPENGL true
#define GP_ERROR_CHECKING true
#define GP_LOGGING true

#if GP_USING_GLFW
#include <GLFW/glfw3.h>
#endif

#include "goopylib/Core/Log.h"

#define MAX_WIDTH 65535
#define MAX_HEIGHT 65535
