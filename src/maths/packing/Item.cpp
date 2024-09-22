#define GP_LOGGING_LEVEl 3

#include "Item.h"
#include "maths/gpmath.h"

namespace gp::packing {
    Item::Item(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_LongSide(max(width, height)),
              m_ShortSide(min(width, height)) {
    }

    void Item::rotate() {
        const float tmp = m_Width;
        m_Width = m_Height;
        m_Height = tmp;

        m_Rotated = !m_Rotated;
    }

    void Item::setHorizontal() {
        if (isVertical())
            rotate();
    }

    void Item::setVertical() {
        if (!isVertical())
            rotate();
    }

    bool Item::isVertical() const {
        return m_Height > m_Width;
    }

    bool Item::isHorizontal() const {
        return m_Width > m_Height;
    }

    bool Item::isRotated() const {
        return m_Rotated;
    }

    float Item::area() const {
        return m_Width * m_Height;
    }

    Point Item::p1() const {
        return {m_X, m_Y};
    }

    Point Item::p2() const {
        return {m_X + m_Width, m_Y + m_Height};
    }

    float Item::getX() const {
        return m_X;
    }

    float Item::getY() const {
        return m_Y;
    }

    void Item::setPosition(float x, float y) {
        m_X = x;
        m_Y = y;
    }

    float Item::getWidth() const {
        return m_Width;
    }

    float Item::getHeight() const {
        return m_Height;
    }

    float Item::getLongSide() const {
        return m_LongSide;
    }

    float Item::getShortSide() const {
        return m_ShortSide;
    }
}
