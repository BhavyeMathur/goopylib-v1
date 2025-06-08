#pragma once

#include "gp.h"

struct Point;

namespace gp::packing {
    class GPAPI Item {

        friend class Bin;

    public:
        /**
         * A class representing a rectangle with some utility methods to be used by Rectangle Packing algorithms.
         *
         * @param width the width of the rectangle
         * @param height the height of the rectangle
         */
        Item(float width, float height);

        /**
         * @return whether the item is oriented vertically, i.e. height > width
         */
        [[nodiscard]] bool isVertical() const;

        /**
         * @return whether the item is oriented vertically, i.e. width < height
         */
        [[nodiscard]] bool isHorizontal() const;

        /**
         * @return whether the item has been rotated from its original orientation
         */
        [[nodiscard]] bool isRotated() const;

        /**
         * @return the area (height * width) of the item
         */
        [[nodiscard]] float area() const;

        /**
         * @return the coordinate of the bottom-left corner
         */
        [[nodiscard]] Point p1() const;

        /**
         * @return the coordinate of the top-right corner
         */
        [[nodiscard]] Point p2() const;

        /**
         * @return the smallest x-coordinate of the item
         */
        [[nodiscard]] float x() const;

        /**
         * @return the smallest y-coordinate of the item
         */
        [[nodiscard]] float y() const;

        /**
         * @return the width of the item
         */
        [[nodiscard]] float width() const;

        /**
         * @return the height of the item
         */
        [[nodiscard]] float height() const;

        /**
         * @return the page (bin) of the rectangle packing the item is located on
         */
        [[nodiscard]] uint32_t page() const;

        /**
         * @return the length of the longer side (i.e. height if vertical, width if horizontal)
         */
        [[nodiscard]] float getLongSide() const;

        /**
         * @return the length of the shorter side (i.e. height if horizontal, width if vertical)
         */
        [[nodiscard]] float getShortSide() const;

        /**
         * Sets the item to its horizontal orientation
         */
        void setHorizontal();

        /**
         * Sets the item to its vertical orientation
         */
        void setVertical();

        /**
         * Rotates the item's orientation
         */
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

        /**
         * Sets the coordinate of the lower-left corner of the item.
         *
         * @param x the x-coordinate
         * @param y the y-coordinate
         */
        void setPosition(float x, float y);

        /**
         * Sets the page (bin) of the rectangle packing the item is located in.
         *
         * @param page the index of the bin
         */
        void setPage(uint32_t page);
    };
}
