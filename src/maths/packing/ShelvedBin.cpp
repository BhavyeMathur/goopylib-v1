#define GP_LOGGING_LEVEl 3

#include "ShelvedBin.h"
#include "Shelf.h"
#include "Item.h"


namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height, uint32_t page)
            : Bin(width, height, page),
              m_Shelves({{0, width}}),
              m_AvailableHeight(height) {
    }

    void ShelvedBin::addShelf() {
        auto &shelf = getOpenShelf();
        shelf.close();
        m_Shelves.push_back({m_PackedHeight, m_Width});
    }

    bool ShelvedBin::fitsOpenShelf(Item &item) const {
        const auto &shelf = m_Shelves.back();
        return item.width() <= shelf.getAvailableWidth() and shelf.getVerticalOffset() + item.height() <= m_Height;
    }

    bool ShelvedBin::fitsShelf(Item &item, Shelf &shelf) const {
        if (shelf.isOpen())
            return item.width() <= shelf.getAvailableWidth() and shelf.getVerticalOffset() + item.height() <= m_Height;
        return item.width() <= shelf.getAvailableWidth() and item.height() <= shelf.height();
    }

    bool ShelvedBin::fitsNewShelf(Item &item) const {
        return item.height() <= m_AvailableHeight;
    }

    void ShelvedBin::add(Item &item, Shelf &shelf) {
        Bin::add(item, shelf.getPackedWidth(), shelf.getVerticalOffset());

        if (item.height() > shelf.height()) {
            m_PackedHeight = shelf.getVerticalOffset() + item.height();
            m_AvailableHeight = m_Height - m_PackedHeight;
        }

        shelf.add(item);
        m_Items.push_back(item);
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
