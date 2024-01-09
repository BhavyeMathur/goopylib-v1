#include "Rectangle.h"

namespace {
    struct TwoPoints {
        Point p1;
        Point p2;
    };

    TwoPoints getUpdatedRectangleVertices(float sin, float cos, Point p1, Point p2) {
        float tan = sin / cos;
        float cot = 1 / tan;

        float x = (p2.y + p1.x * tan + p2.x * cot - p1.y) / (tan + cot);
        float y = tan * (x - p1.x) + p1.y;

        return {{p1.x - (x - p2.x), p1.y - (y - p2.y)}, {x, y}};
    }
}

namespace gp {
    void Rectangle::setP1(Point point) {
        TwoPoints p = getUpdatedRectangleVertices(m_SinAngle, m_CosAngle, point, m_Points[2]);

        m_Points[0] = point;
        m_Points[1] = p.p1;
        m_Points[3] = p.p2;

        _calculateAttributes();
        update();
    }

    Point Rectangle::getP1() const {
        return m_Points[0];
    }

    void Rectangle::setP2(Point point) {
        TwoPoints p = getUpdatedRectangleVertices(m_SinAngle, m_CosAngle, point, m_Points[3]);

        m_Points[1] = point;
        m_Points[2] = p.p1;
        m_Points[0] = p.p2;

        _calculateAttributes();
        update();
    }

    Point Rectangle::getP2() const {
        return m_Points[1];
    }

    void Rectangle::setP3(Point point) {
        TwoPoints p = getUpdatedRectangleVertices(m_SinAngle, m_CosAngle, point, m_Points[0]);

        m_Points[2] = point;
        m_Points[3] = p.p1;
        m_Points[1] = p.p2;

        _calculateAttributes();
        update();
    }

    Point Rectangle::getP3() const {
        return m_Points[2];
    }

    void Rectangle::setP4(Point point) {
        TwoPoints p = getUpdatedRectangleVertices(m_SinAngle, m_CosAngle, point, m_Points[1]);

        m_Points[3] = point;
        m_Points[0] = p.p1;
        m_Points[2] = p.p2;

        _calculateAttributes();
        update();
    }

    Point Rectangle::getP4() const {
        return m_Points[3];
    }
}
