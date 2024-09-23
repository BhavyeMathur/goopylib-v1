#include "Shelf.h"
#include "ShelvedBin.h"
#include "Item.h"

#include "debug/Error.h"


namespace gp::packing {
    Shelf::Shelf(float verticalOffset, float width)
            : m_Width(width),
              m_AvailableWidth(width),
              m_VerticalOffset(verticalOffset) {

    }

    bool Shelf::fitsItemVertically(const Item &item) const {
        return item.getLongSide() <= m_Height;
    }

    void Shelf::add(Item &item) {
        GP_CHECK_LE(item.width(), m_AvailableWidth, "Item does not fit into shelf")

        item.setPosition(m_PackedWidth, m_VerticalOffset);
        m_PackedWidth += item.width();
        m_AvailableWidth -= item.width();

        if (item.height() > m_Height)
            m_Height = item.height();
    }
}

namespace gp::packing {
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
