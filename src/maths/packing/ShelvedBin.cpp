#define GP_LOGGING_LEVEl 3

#include "ShelvedBin.h"
#include "Shelf.h"
#include "Item.h"


namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height)
            : Bin(width, height),
              m_Shelves({{0, *this}}) {
    }

    shelf::Shelf &ShelvedBin::addShelf() {
        auto shelf = getOpenShelf();
        shelf.close();

        m_Shelves.push_back({shelf.m_VerticalOffset + shelf.m_Height, *this});
        return getOpenShelf();
    }

    float ShelvedBin::packingRatio() const {
        float sum = 0.0f;
        float area = 0.0f;

        for (const auto &item: m_Items)
            sum += item.area();

        for (const auto &shelf: m_Shelves)
            area += shelf.area();

        return sum / area;
    }

    shelf::Shelf &ShelvedBin::getOpenShelf() {
        return m_Shelves.back();
    }

    const std::vector<shelf::Shelf> &ShelvedBin::getShelves() const {
        return m_Shelves;
    }

    std::vector<shelf::Shelf>::iterator ShelvedBin::begin() {
        return m_Shelves.begin();
    }

    std::vector<shelf::Shelf>::iterator ShelvedBin::end() {
        return m_Shelves.end();
    }
}
