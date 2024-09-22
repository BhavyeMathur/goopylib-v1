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

        [[nodiscard]] float x() const;

        [[nodiscard]] float y() const;

        // TODO setPosition() and rotate() mutate the item and should not be public
        void setPosition(float x, float y, uint32_t page);

        [[nodiscard]] float width() const;

        [[nodiscard]] float height() const;

        [[nodiscard]] uint32_t page() const;

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
        uint32_t m_Page = -1;

        bool m_Rotated = false;
    };
}
