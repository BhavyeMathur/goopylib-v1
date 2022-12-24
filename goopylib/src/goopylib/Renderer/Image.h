#pragma once

#include "RenderableObject.h"


namespace gp {
    class Image : public RenderableObject {

        friend class Renderer;

    public:
        Image(Point position, const char *path);

        Image(Point position, const char *path, float width, float height);

        Image(Point p1, Point p2, const char *path);

        const char *getPath() const;

        void setTransparency(float value);

        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        ImageVertexAttrib m_V1 = {{0, 0}};
        ImageVertexAttrib m_V2 = {{1, 0}};
        ImageVertexAttrib m_V3 = {{1, 1}};
        ImageVertexAttrib m_V4 = {{0, 1}};

        const char *m_Path;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;
    };
}
