#include "NextFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    NextFit::NextFit(float binWidth, float binHeight)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_Shelf(m_Bins.back()->m_OpenShelf) {
    }

    void NextFit::pack(Item &item, bool allowRotation) {
        if (allowRotation and (item.isVertical() != (item.getLongSide() <= m_Shelf->getHeight())))
            item.rotate();

        if (m_Shelf->fits(item))
            return addItemToShelf(item, *m_Shelf);

        if (m_Shelf->fitsAbove(item))
            m_Shelf = m_Bins.back()->addShelf();
        else {
            m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));
            m_Shelf = m_Bins.back()->m_OpenShelf;
        }

        if (allowRotation and item.isVertical())
            item.rotate();

        return addItemToShelf(item, *m_Shelf);
    }
}
