#include "ShelvedBin.h"
#include "Shelf.h"
#include "Item.h"

namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height)
            : Bin(width, height),
              m_Shelves({{0, *this}}),
              m_OpenShelf(&m_Shelves[0]) {
    }

    shelf::Shelf &ShelvedBin::addShelf() {
        m_OpenShelf->close();

        m_Shelves.push_back({m_OpenShelf->m_VerticalOffset + m_OpenShelf->m_Height, *this});
        m_OpenShelf = &m_Shelves.back();

        return *m_OpenShelf;
    }

    float ShelvedBin::packingRatio() const {
        if (m_ID != Bin::s_Bins - 1)  // this is not the latest bin
            return Bin::packingRatio();

        float sum = 0.0f;
        float area = 0.0f;

        for (const auto &item: m_Items)
            sum += item->area();

        for (const auto &shelf: m_Shelves)
            area += shelf.packedArea();

        return sum / area;
    }

    shelf::Shelf &ShelvedBin::getOpenShelf() {
        return *m_OpenShelf;
    }

    const std::vector<shelf::Shelf> &ShelvedBin::getShelves() {
        return m_Shelves;
    }

    std::vector<shelf::Shelf>::iterator ShelvedBin::begin() {
        return m_Shelves.begin();
    }

    std::vector<shelf::Shelf>::iterator ShelvedBin::end() {
        return m_Shelves.end();
    }
}
