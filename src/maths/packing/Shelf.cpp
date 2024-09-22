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
        return strformat("Shelf(offset=%f, packed=%f) with %i items", m_VerticalOffset, m_PackedWidth, m_Items.size());
    }

    std::ostream &operator<<(std::ostream &os, const Shelf &shelf) {
        os << shelf.toString();
        return os;
    }

    float Shelf::packedArea() const {
        if (m_IsOpen)
            return m_PackedWidth * m_Height;
        return m_Width * m_Height;
    }

    bool Shelf::fits(const Item &item) const {
        if (m_IsOpen)
            return item.getWidth() <= m_AvailableWidth and m_VerticalOffset + item.getHeight() <= m_Bin.getHeight();
        return item.getWidth() <= m_AvailableWidth and item.getHeight() <= m_Height;
    }

    bool Shelf::fitsAbove(const Item &item) const {
        return m_VerticalOffset + m_Height + item.getHeight() <= m_Bin.getHeight();
    }

    void Shelf::add(Item &item) {
        item.setPosition(m_PackedWidth, m_VerticalOffset);
        m_Bin.add(item);
        m_Items.push_back(&item);

        if (item.getHeight() > m_Height)
            m_Height = item.getHeight();

        m_PackedWidth += item.getWidth();
        m_AvailableWidth -= item.getWidth();
    }
}

namespace gp::packing::shelf {
    float Shelf::getWidth() const {
        return m_Width;
    }

    float Shelf::getHeight() const {
        return m_Height;
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
