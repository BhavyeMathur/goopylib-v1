#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"
#include "src/goopylib/Shader/Shader.h"


namespace gp {

    class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3);

        ~Triangle();

        void draw(Window *window);

        void destroy();

    private:
        Point m_Position;
        Point m_P1, m_P2, m_P3;

        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;
        bool m_Drawn = false;
    };
}
