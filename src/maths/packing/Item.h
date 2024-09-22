#pragma once

#include "gp.h"

struct Point;

namespace gp::packing {
    class GPAPI Item {
    public:
        Item(float width, float height);

        [[nodiscard]] bool isVertical() const;

        [[nodiscard]] bool isHorizontal() const;

        [[nodiscard]] bool isRotated() const;

        [[nodiscard]] float area() const;

        [[nodiscard]] Point p1() const;

        [[nodiscard]] Point p2() const;

        [[nodiscard]] float getX() const;

        [[nodiscard]] float getY() const;

        // TODO setPosition() and rotate() mutate the item and should not be public
        void setPosition(float x, float y);

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

        [[nodiscard]] float getLongSide() const;

        [[nodiscard]] float getShortSide() const;

        void setHorizontal();

        void setVertical();

        void rotate();

    private:
        float m_Width;
        float m_Height;
        float m_LongSide;
        float m_ShortSide;

        float m_X = -1;
        float m_Y = -1;

        bool m_Rotated = false;
    };
}
