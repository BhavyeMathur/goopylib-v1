#include "PackingCore.h"


// Item Class
namespace gp {
    uint32_t Item::items = 0;

    Item::Item(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Item::items),
              m_LongSide(max(width, height)),
              m_ShortSide(min(width, height)) {
        Item::items++;
    }

    void Item::rotate() {
        float tmp = m_Width;
        m_Width = m_Height;
        m_Height = tmp;

        m_Rotated = !m_Rotated;
    }

    bool Item::isVertical() const {
        return m_Height > m_Width;
    }

    bool Item::isHorizontal() const {
        return m_Width > m_Height;
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

    float Item::isRotated() const {
        return m_Rotated;
    }
}

// Bin Class
namespace gp {
    uint32_t Bin::bins = 0;

    Bin::Bin(float width, float height)
            : m_Width(width),
            m_Height(height),
            m_ID(Bin::bins) {
        Bin::bins++;
    }

    void Bin::add(Item &item) {
        m_Items.push_back(&item);
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (const auto &item: m_Items) {
            sum += item.area();
        }

        return sum / (m_Width * m_Height);
    }
}
