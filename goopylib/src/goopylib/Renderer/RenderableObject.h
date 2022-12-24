#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"

namespace gp {
    struct Scale {
        float xscale;
        float yscale;
    };
}

namespace gp {


    class RenderableObject {

        friend class Renderer;

    public:
        void draw(Window *window);

        void destroy();

        bool isDrawn() const;

        // Anchor
        void setAnchor(float x, float y);

        void resetAnchor() {
            float sumX = 0;
            float sumY = 0;

            for (int i = 0; i < m_Vertices; i++) {
                Point p = m_Points[i];

                sumX += p.x;
                sumY += p.y;
            }

            m_Position = {sumX / (float) m_Vertices, sumY / (float) m_Vertices};
        }

        // Position
        void setPosition(float x, float y);

        Point getPosition() const;

        void move(float dx, float dy);

        // Rotation
        void rotate(float angle);

        float getRotation() const;

        // Scale
        void scale(float factor);

        void scale(float xfactor, float yfactor);

        Scale getScale() const;

        // Dimensions
        void setWidth(float width) {
            scale(width / m_Width, 1);
            m_Width = width;
        }

        float getWidth() const {
            return m_Width;
        }

        void setHeight(float height) {
            scale(1, height / m_Height);
            m_Height = height;
        }

        float getHeight() const {
            return m_Height;
        }

        void setSize(float width, float height) {
            scale(width / m_Width, height / m_Height);
            m_Width = width;
            m_Height = height;
        }

        bool contains(Point point);

        bool contains(float x, float y);

    protected:
        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;

        Point *m_Points = nullptr;
        uint32_t m_Vertices;

        Point m_Position = {0, 0};
        float m_Width;
        float m_Height;

        float m_MaxX = -FLT_MAX;
        float m_MinX = FLT_MAX;
        float m_MaxY = -FLT_MAX;
        float m_MinY = FLT_MAX;

        float m_Angle = 0;
        float m_xScale = 1;
        float m_yScale = 1;

        RenderableObject(Point position, std::initializer_list<Point> points);

        RenderableObject(std::initializer_list<Point> points);

        void update() const;

    protected:
        void _move(float dx, float dy) {
            for (int i = 0; i < m_Vertices; i++) {
                m_Points[i].x += dx;
                m_Points[i].y += dy;
            }
        }

        void _rotate(float sin, float cos) {
            for (int i = 0; i < m_Vertices; i++) {
                Point p = m_Points[i];

                m_Points[i] = {p.x * cos + p.y * sin,
                               p.y * cos - p.x * sin};
            }
        }

        void _scale(float xfactor, float yfactor) {
            for (int i = 0; i < m_Vertices; i++) {
                m_Points[i].x *= xfactor;
                m_Points[i].y *= yfactor;
            }
        }

        virtual bool _contains(float x, float y) {
            return false;
        };

    private:
        bool m_Drawn = false;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;
    };
}
