#pragma once

#include "gp.h"
#include "src/goopylib/maths/gpmath.h"

// Item Class
namespace gp {
    class Item {

    public:
        GPAPI Item(float width, float height);

        GPAPI ~Item() = default;

        GPAPI bool isVertical() const;

        GPAPI bool isHorizontal() const;

        GPAPI float area() const;

        GPAPI Point p1() const;

        GPAPI Point p2() const;

        GPAPI float getX() const;

        GPAPI float getY() const;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

        GPAPI float getLongSide() const;

        GPAPI float getShortSide() const;

        GPAPI float isRotated() const;

    private:
        float m_Width;
        float m_Height;
        float m_LongSide;
        float m_ShortSide;

        float m_X = -1;
        float m_Y = -1;

        bool m_Rotated = false;

        uint32_t m_ID;
        static uint32_t items;

        void rotate();
    };
}

// Bin Class
namespace gp {
    class Bin {
        GPAPI float packingRatio() const;

    private:
        float m_Width;
        float m_Height;

        std::vector<Item *> m_Items;

        uint32_t m_ID;
        static uint32_t bins;

        Bin(float width, float height);

        ~Bin() = default;

        void add(Item &item);
    };
}
