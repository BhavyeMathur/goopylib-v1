#include "ShelvedBin.h"
#include "Shelf.h"
#include "Item.h"

#include "debug/Error.h"


namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height, uint32_t page)
            : Bin(width, height, page),
              m_Shelves({{0, width}}),
              m_AvailableHeight(height) {
    }

    void ShelvedBin::addShelf() {
        m_Shelves.back().close();
        m_Shelves.push_back({m_PackedHeight, m_Width});
    }

    bool ShelvedBin::fitsOpenShelf(Item &item) const {
        const auto &shelf = m_Shelves.back();
        return shelf.fitsItemHorizontally(item) and shelf.y() + item.height() <= m_Height;
    }

    bool ShelvedBin::fitsShelf(Item &item, Shelf &shelf) const {
        if (shelf.isOpen())
            return shelf.fitsItemHorizontally(item) and shelf.y() + item.height() <= m_Height;
        return shelf.fitsItemHorizontally(item) and item.height() <= shelf.height();
    }

    bool ShelvedBin::fitsNewShelf(Item &item) const {
        return item.height() <= m_AvailableHeight;
    }

    void ShelvedBin::add(Item &item, Shelf &shelf) {
        // If the item's height exceeds the shelf's current height, we must resize the shelf and update the
        // available & packed height in the bin
        if (item.height() > shelf.height()) {
            m_PackedHeight = shelf.y() + item.height();
            m_AvailableHeight = m_Height - m_PackedHeight;

            GP_CHECK_GE(m_AvailableHeight, 0, strformat("Item with height %i does not fit into shelf", item.height()));
        }

        Bin::add(item, shelf.packedWidth(), shelf.y());
        shelf.add(item);
    }

    Shelf &ShelvedBin::getOpenShelf() {
        return m_Shelves.back();
    }

    const std::vector<Shelf> &ShelvedBin::getShelves() const {
        return m_Shelves;
    }

    std::vector<Shelf>::iterator ShelvedBin::begin() {
        return m_Shelves.begin();
    }

    std::vector<Shelf>::iterator ShelvedBin::end() {
        return m_Shelves.end();
    }
}
