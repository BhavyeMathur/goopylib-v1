#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"
#include "src/goopylib/Core/Shader.h"


namespace gp {

    class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3);
        ~Triangle();

        void draw(const Ref<Window>& window);

        void destroy();

        static void bindShader();

        static Ref<Triangle> create(Point p1, Point p2, Point p3);

    private:
        Point m_Position;
        Point m_P1, m_P2, m_P3;

        Ref<Window> m_Window;
        uint32_t m_RendererID = 0;
        bool m_Drawn = false;

        static Scope<Shader> s_Shader;
    };
}
