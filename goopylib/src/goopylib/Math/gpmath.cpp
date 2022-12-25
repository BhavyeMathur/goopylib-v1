#include "gpmath.h"


bool checkTriangleContains(Point point, Point a, Point b, Point c) {
    float px_minus_ax = point.x - a.x;
    float py_minus_ay = point.y - a.y;

    bool s_ab = (b.x - a.x) * py_minus_ay - (b.y - a.y) * px_minus_ax > 0;

    if ((c.x - a.x) * py_minus_ay - (c.y - a.y) * px_minus_ax > 0 == s_ab) {
        return false;
    }

    return (c.x - b.x) * (point.y - b.y) - (c.y - b.y) * (point.x - b.x) > 0 == s_ab;
}

bool checkQuadContains(Point point, Point a, Point b, Point c, Point d) {
    float px_minus_ax = point.x - a.x;
    float py_minus_ay = point.y - a.y;
    float cx_minus_ax = c.x - a.x;
    float cy_minus_ay = c.y - a.y;

    bool s_ab = (b.x - a.x) * py_minus_ay - (b.y - a.y) * px_minus_ax > 0;

    if ((cx_minus_ax * py_minus_ay - cy_minus_ay * px_minus_ax > 0 == s_ab)
        or ((c.x - b.x) * (point.y - b.y) - (c.y - b.y) * (point.x - b.x) > 0 != s_ab)) {

        bool s_ac = cx_minus_ax * py_minus_ay - cy_minus_ay * px_minus_ax > 0;

        if ((d.x - a.x) * py_minus_ay - (d.y - a.y) * px_minus_ax > 0 == s_ac) {
            return false;
        }
        return (d.x - c.x) * (point.y - c.y) - (d.y - c.y) * (point.x - c.x) > 0 == s_ac;

    }

    return true;
}

uint32_t uint32_rgb(float red, float green, float blue) {
    int32_t val = 0;

    val = val | ((int) (1) << 24);
    val = val | ((int) (blue * 255) << 16);
    val = val | ((int) (green * 255) << 8);
    val = val | ((int) (red * 255) << 0);

    return val;
}
