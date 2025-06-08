#include "Shelf.h"
#include "ShelvedBin.h"
#include "Item.h"

#include "debug/Error.h"


namespace gp::packing {
    Shelf::Shelf(float y, float width)
            : m_Width(width),
              m_AvailableWidth(width),
              m_Y(y) {
    }

    bool Shelf::fitsItemVertically(const Item &item) const {
        return item.getLongSide() <= m_Height;
    }

    bool Shelf::fitsItemHorizontally(const Item &item) const {
        return item.width() <= m_AvailableWidth;
    }

    void Shelf::add(Item &item) {
        GP_CHECK_LE(item.width(), m_AvailableWidth, "Item does not fit into shelf")

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

    float Shelf::y() const {
        return m_Y;
    }

    float Shelf::packedWidth() const {
        return m_PackedWidth;
    }

    float Shelf::availableWidth() const {
        return m_AvailableWidth;
    }

    bool Shelf::isOpen() const {
        return m_IsOpen;
    }

    void Shelf::close() {
        m_IsOpen = false;
    }
}
