#pragma once

#if __APPLE__

#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#if GP_DRAW_MODE_TRIANGLES != GL_TRIANGLES
static_assert(false, "GP_DRAW_MODE_TRIANGLES != GL_TRIANGLES");
#endif

#if GP_DRAW_MODE_LINES != GL_LINES
static_assert(false, "GP_DRAW_MODE_LINES != GL_LINES");
#endif
