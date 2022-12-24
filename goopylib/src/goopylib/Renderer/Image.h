#pragma once

#include "Polygon4.h"


namespace gp {
    class Image : public Polygon4<ImageVertexAttrib> {

        friend class Renderer;

    public:
        Image(Point position, const char *path);

        Image(Point position, const char *path, float width, float height);

        Image(Point p1, Point p2, const char *path);

        const char *getPath() const;

    private:
        const char *m_Path;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;
    };
}
