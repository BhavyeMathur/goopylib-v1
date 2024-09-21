#define GP_LOGGING_LEVEl 3

#include "Shelf.h"
#include "Bin.h"
#include "Item.h"


namespace gp::packing::shelf {
    Shelf::Shelf(float verticalOffset, Bin &bin)
            : m_Width(bin.getWidth()),
              m_AvailableWidth(bin.getWidth()),
              m_VerticalOffset(verticalOffset),
              m_Bin(bin) {

    }

    std::string Shelf::toString() const {
        return strformat("Shelf(offset=%f, packed=%f) with %i items", m_VerticalOffset, m_PackedWidth, m_Items.size());
    }

    float Shelf::packedArea() const {
        if (m_IsOpen) {
            return m_PackedWidth * m_Height;
        } else {
            return m_Width * m_Height;
        }
    }

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

    bool Shelf::fits(const shared_ptr<Item> &item) const {
        if (m_IsOpen) {
            return item->getWidth() <= m_AvailableWidth and
                   m_VerticalOffset + item->getHeight() <= m_Bin.getHeight();
        } else {
            return item->getWidth() <= m_AvailableWidth and item->getHeight() <= m_Height;
        }
    }

    bool Shelf::fitsAbove(const shared_ptr<Item> &item) const {
        return m_VerticalOffset + m_Height + item->getHeight() <= m_Bin.getHeight();
    }

    void Shelf::add(const shared_ptr<Item> &item) {
        item->setX(m_PackedWidth);
        item->setY(m_VerticalOffset);
        m_Bin.add(item);
        m_Items.push_back(item);

        if (item->getHeight() > m_Height) {
            m_Height = item->getHeight();
        }

        m_PackedWidth += item->getWidth();
        m_AvailableWidth -= item->getWidth();
    }

    void Shelf::close() {
        m_IsOpen = false;
    }

    std::ostream &operator<<(std::ostream &os, const Shelf &shelf) {
        os << shelf.toString();
        return os;
    }
}
