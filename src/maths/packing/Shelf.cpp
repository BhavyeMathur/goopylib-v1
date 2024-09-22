#define GP_LOGGING_LEVEl 3

#include "Shelf.h"
#include "ShelvedBin.h"
#include "Item.h"


namespace gp::packing::shelf {
    Shelf::Shelf(float verticalOffset, ShelvedBin &bin)
            : m_Width(bin.getWidth()),
              m_AvailableWidth(bin.getWidth()),
              m_VerticalOffset(verticalOffset),
              m_Bin(bin) {

    }

    std::string Shelf::toString() const {
        return strformat("Shelf(offset=%f, packed=%f)", m_VerticalOffset, m_PackedWidth);
    }

    std::ostream &operator<<(std::ostream &os, const Shelf &shelf) {
        os << shelf.toString();
        return os;
    }

    bool Shelf::fits(const Item &item) const {
        if (m_IsOpen)
            return item.width() <= m_AvailableWidth and m_VerticalOffset + item.height() <= m_Bin.getHeight();
        return item.width() <= m_AvailableWidth and item.height() <= m_Height;
    }

    bool Shelf::fitsShelfAbove(const Item &item) const {
        return m_VerticalOffset + m_Height + item.height() <= m_Bin.getHeight();
    }

    bool Shelf::fitsItemVertically(const Item &item) const {
        return item.getLongSide() <= m_Height;
    }

    void Shelf::add(Item &item) {
        item.setPosition(m_PackedWidth, m_VerticalOffset);
        m_Bin.add(item);

        if (item.height() > m_Height)
            m_Height = item.height();

        m_PackedWidth += item.width();
        m_AvailableWidth -= item.width();
    }
}

namespace gp::packing::shelf {
    float Shelf::width() const {
        return m_Width;
    }

    float Shelf::height() const {
        return m_Height;
    }

    float Shelf::area() const {
        return m_Width * m_Height;
    }

    float Shelf::getVerticalOffset() const {
        return m_VerticalOffset;
    }

    float Shelf::getPackedWidth() const {
        return m_PackedWidth;
    }

    float Shelf::getAvailableWidth() const {
        return m_AvailableWidth;
    }

    bool Shelf::isOpen() const {
        return m_IsOpen;
    }

    void Shelf::close() {
        m_IsOpen = false;
    }
}
