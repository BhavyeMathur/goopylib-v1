#pragma once

#include "RenderableObject.h"

namespace gp {
    template<typename VertexType>
        class Polygon4 : public RenderableObject {
        public:
            void setTransparency(float value) {
                m_V1.transparency = value;
                m_V2.transparency = value;
                m_V3.transparency = value;
                m_V4.transparency = value;

                update();
            }

            void setTransparency(float v1, float v2, float v3, float v4) {
                m_V1.transparency = v1;
                m_V2.transparency = v2;
                m_V3.transparency = v3;
                m_V4.transparency = v4;

                update();
            }

        protected:
            VertexType m_V1, m_V2, m_V3, m_V4;

            Polygon4(Point position,
                     Point p1, VertexType V1,
                     Point p2, VertexType V2,
                     Point p3, VertexType V3,
                     Point p4, VertexType V4)
                    : RenderableObject(position, {p1, p2, p3, p4}),
                    m_V1(V1),
                    m_V2(V2),
                    m_V3(V3),
                    m_V4(V4) {
            }

            Polygon4(Point p1, VertexType V1,
                     Point p2, VertexType V2,
                     Point p3, VertexType V3,
                     Point p4, VertexType V4)
                    : RenderableObject({p1, p2, p3, p4}),
                    m_V1(V1),
                    m_V2(V2),
                    m_V3(V3),
                    m_V4(V4) {
            }

            Polygon4(Point p1, Point p2)
                    : RenderableObject({{p1.x, p1.y},
                                        {p2.x, p1.y},
                                        {p2.x, p2.y},
                                        {p1.x, p2.y}}) {

            }

            bool _contains(float x, float y) override {
                return false;
            };
        };
}
