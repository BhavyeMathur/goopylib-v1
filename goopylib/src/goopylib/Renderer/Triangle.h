#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"


namespace gp {
    class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3);

        ~Triangle();

        void draw(Window *window);

        void destroy();

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3);

    private:
        Point m_Position;
        TriangleVertex m_V1, m_V2, m_V3;

        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;
        bool m_Drawn = false;
    };
}
