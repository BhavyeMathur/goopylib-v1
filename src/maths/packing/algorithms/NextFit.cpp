#include "NextFit.h"


namespace gp::packing::shelf {
    NextFit::NextFit(float binWidth, float binHeight) : ShelfPackingAlgorithm(binWidth, binHeight),
                                                        m_Shelf{&m_Bins.back().getOpenShelf()} {
    }

    void NextFit::pack(Item &item, bool allowRotation) {
        orientItemForShelf(item, *m_Shelf, allowRotation);
        if (m_Shelf->fits(item))
            return addItemToShelf(item, *m_Shelf);

        if (!tryAddingToNewShelf(item, *m_Shelf, m_Bins.back(), allowRotation))
            addItemToNewBin(item, false);  // allowRotation false since item is horizontal after tryAddingToNewShelf

        m_Shelf = &m_Bins.back().getOpenShelf();
    }
}
