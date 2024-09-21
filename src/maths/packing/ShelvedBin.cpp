#include "ShelvedBin.h"
#include "Shelf.h"
#include "Item.h"

namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height)
            : Bin(width, height),
              m_OpenShelf(shared_ptr<shelf::Shelf>(new shelf::Shelf(0, *this))) {
        m_Shelves.push_back(m_OpenShelf);
    }

    shared_ptr<shelf::Shelf> ShelvedBin::addShelf() {
        m_OpenShelf->close();
        m_OpenShelf = shared_ptr<shelf::Shelf>(new shelf::Shelf(m_OpenShelf->m_VerticalOffset + m_OpenShelf->m_Height, *this));
        m_Shelves.push_back(m_OpenShelf);

        return m_OpenShelf;
    }

    float ShelvedBin::packingRatio() const {
        if (m_ID == Bin::s_Bins - 1) { // this is the latest bin
            float sum = 0;
            float area = 0;
            for (const auto &item: m_Items) {
                sum += item->area();
            }
            for (const auto &shelf: m_Shelves) {
                area += shelf->packedArea();
            }

            return sum / area;
        }
        return Bin::packingRatio();
    }

    shared_ptr<shelf::Shelf> ShelvedBin::getOpenShelf() {
        return m_OpenShelf;
    }

    std::vector<shared_ptr<shelf::Shelf>> ShelvedBin::getShelves() {
        std::vector<shared_ptr<shelf::Shelf>> copy = m_Shelves;
        return copy;
    }

    std::vector<shared_ptr<shelf::Shelf>>::const_iterator ShelvedBin::begin() const {
        return m_Shelves.begin();
    }

    std::vector<shared_ptr<shelf::Shelf>>::const_iterator ShelvedBin::end() const {
        return m_Shelves.end();
    }
}
