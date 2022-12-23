#pragma once

#include "RenderableObject.h"

namespace gp {
    template<typename VertexType>
        class Polygon4 : public RenderableObject {
        public:
            void resetCenter() final {
                m_Position.x = (m_V1.point.x + m_V2.point.x + m_V3.point.x + m_V4.point.x) / 4.0f;
                m_Position.y = (m_V1.point.y + m_V2.point.y + m_V3.point.y + m_V4.point.y) / 4.0f;
            }

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

        protected:
            VertexType m_V1, m_V2, m_V3, m_V4;

            float m_Width;
            float m_Height;

            Polygon4(Point position, VertexType V1, VertexType V2, VertexType V3, VertexType V4,
                     float width, float height)
                    : RenderableObject(position),
                    m_V1(V1),
                    m_V2(V2),
                    m_V3(V3),
                    m_V4(V4),
                    m_Width(width),
                    m_Height(height) {
            }

            Polygon4(Point p1, Point p2)
                    : RenderableObject({(p1.x + p2.x) / 2.0f, (p1.y + p2.y) / 2.0f}),
                    m_Width(abs(p2.x - p1.x)),
                    m_Height(abs(p2.y - p1.y)) {

            }

            void _move(float dx, float dy) final {
                m_V1.point.x += dx;
                m_V1.point.y += dy;

                m_V2.point.x += dx;
                m_V2.point.y += dy;

                m_V3.point.x += dx;
                m_V3.point.y += dy;

                m_V4.point.x += dx;
                m_V4.point.y += dy;
            }

            void _rotate(float sin, float cos) final {
                m_V1.point = {m_V1.point.x * cos + m_V1.point.y * sin,
                              m_V1.point.y * cos - m_V1.point.x * sin};

                m_V2.point = {m_V2.point.x * cos + m_V2.point.y * sin,
                              m_V2.point.y * cos - m_V2.point.x * sin};

                m_V3.point = {m_V3.point.x * cos + m_V3.point.y * sin,
                              m_V3.point.y * cos - m_V3.point.x * sin};

                m_V4.point = {m_V4.point.x * cos + m_V4.point.y * sin,
                              m_V4.point.y * cos - m_V4.point.x * sin};
            }

            void _scale(float xfactor, float yfactor) final {
                m_V1.point.x *= xfactor;
                m_V1.point.y *= yfactor;

                m_V2.point.x *= xfactor;
                m_V2.point.y *= yfactor;

                m_V3.point.x *= xfactor;
                m_V3.point.y *= yfactor;

                m_V4.point.x *= xfactor;
                m_V4.point.y *= yfactor;
            }
        };
}
