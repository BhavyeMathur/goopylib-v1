#define GP_LOGGING_LEVEl 3

#include "Shelf.h"

#include <cfloat>
#include <utility>


// Shelf Class
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
        }
        else {
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
        }
        else {
            return item->getWidth() <= m_AvailableWidth and item->getHeight() <= m_Height;
        }
    }

    bool Shelf::fitsAbove(const shared_ptr<Item> &item) const {
        return m_VerticalOffset + m_Height + item->getHeight() <= m_Bin.getHeight();
    }

    void Shelf::add(const shared_ptr<Item> &item) {
        item->m_X = m_PackedWidth;
        item->m_Y = m_VerticalOffset;
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

// Shelved Bin Class
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

// Shelf Packing Algorithms
namespace gp::packing::shelf {
    ShelfPackingAlgorithm::ShelfPackingAlgorithm(float binWidth, float binHeight)
            : PackingAlgorithm(binWidth, binHeight) {
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
    }

    ShelfPackingAlgorithm::ShelfPackingAlgorithm()
            : PackingAlgorithm(0, 0) {
    }

    void ShelfPackingAlgorithm::pack(const shared_ptr<Item> &item, bool allowRotation) {
        GP_RUNTIME_ERROR("ShelfPackingAlgorithm::pack() unimplemented");
    }

    void ShelfPackingAlgorithm::packAll(std::vector<shared_ptr<Item>> items,
                                        bool allowRotation,
                                        const SortingFunction &sortingFunction) {
        if (sortingFunction) {
            items = sortingFunction(items);
        }
        for (const auto &item: items) {
            pack(item, allowRotation);
        }
    }

    void ShelfPackingAlgorithm::packOriented(const shared_ptr<Item> &item, bool orientVertically) {
        if (item->isHorizontal() == orientVertically) {
            item->rotate();
        }
        pack(item, false);
    }

    void ShelfPackingAlgorithm::packAllOriented(std::vector<shared_ptr<Item>> items,
                                                bool orientVertically,
                                                const SortingFunction &sortingFunction) {
        if (sortingFunction) {
            items = sortingFunction(items);
        }
        for (auto &item: items) {
            packOriented(item, orientVertically);
        }
    }

    std::vector<shared_ptr<ShelvedBin>> ShelfPackingAlgorithm::bins() const {
        std::vector<shared_ptr<ShelvedBin>> copy = m_Bins;
        return copy;
    }

    NextFit::NextFit(float binWidth, float binHeight)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_Shelf(m_Bins.back()->m_OpenShelf) {
    }

    void NextFit::pack(const shared_ptr<Item> &item, bool allowRotation) {
        if (allowRotation and (item->isVertical() != (item->getLongSide() <= m_Shelf->getHeight()))) {
            item->rotate();
        }

        if (m_Shelf->fits(item)) {
            m_Shelf->add(item);
            return;
        }

        if (m_Shelf->fitsAbove(item)) {
            m_Shelf = m_Bins.back()->addShelf();
        }
        else {
            m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));
            m_Shelf = m_Bins.back()->m_OpenShelf;
        }

        if (allowRotation and item->isVertical()) {
            item->rotate();
        }
        m_Shelf->add(item);
    }

    FirstFit::FirstFit(float binWidth, float binHeight)
            : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void FirstFit::pack(const shared_ptr<Item> &item, bool allowRotation) {
        for (const auto &bin: m_Bins) {
            for (const auto &shelf: *bin) {
                if (allowRotation and (item->isVertical() != (item->getLongSide() <= shelf->getHeight()))) {
                    item->rotate();
                }

                if (shelf->fits(item)) {
                    shelf->add(item);
                    return;
                }
            }

            if (bin->m_OpenShelf->fitsAbove(item)) {
                if (allowRotation and item->isVertical()) {
                    item->rotate();
                }
                bin->addShelf()->add(item);
                return;
            }
        }
        // code only reaches here if item has not been added to a shelf
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));

        if (allowRotation and item->isVertical()) {
            item->rotate();
        }
        const auto &newBin = m_Bins.back();
        const auto &newShelf = newBin->m_OpenShelf;
        newShelf->add(item);
    }

    ScoredFit::ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_ScoringFunction(std::move(scoringFunction)) {
    }

    void ScoredFit::pack(const shared_ptr<Item> &item, bool allowRotation) {
        shared_ptr<Shelf> bestShelf = nullptr;
        float bestScore = -FLT_MAX;
        bool bestOrientation = false;  // un-rotated

        for (const auto &bin: m_Bins) {
            for (const auto &shelf: *bin) {
                if (allowRotation and (item->isVertical() != (item->getLongSide() <= shelf->getHeight()))) {
                    item->rotate();
                }

                if (shelf->fits(item)) {
                    float score = m_ScoringFunction(shelf, item);
                    if (score > bestScore) {
                        bestShelf = shelf;
                        bestScore = score;
                        bestOrientation = item->isRotated();
                    }
                }
            }

            if (bestShelf == nullptr and bin->m_OpenShelf->fitsAbove(item)) {
                auto shelf = bin->addShelf();

                float score = m_ScoringFunction(shelf, item);
                if (score > bestScore) {
                    bestShelf = shelf;
                    bestScore = score;
                    bestOrientation = item->isRotated();
                }
            }
        }

        if (bestShelf == nullptr) {
            m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));

            if (allowRotation and item->isVertical()) {
                item->rotate();
            }

            bestShelf = m_Bins.back()->m_OpenShelf;
            bestOrientation = item->isRotated();
        }

        if (item->isRotated() != bestOrientation) {
            item->rotate();
        }
        bestShelf->add(item);
    }

    BestWidthFit::BestWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return obj->getWidth() - shelf->getAvailableWidth();
                        }) {
    }

    WorstWidthFit::WorstWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return shelf->getAvailableWidth() - obj->getWidth();
                        }) {
    }

    BestHeightFit::BestHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return obj->getHeight() - shelf->getHeight();
                        }) {
    }

    WorstHeightFit::WorstHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return shelf->getHeight() - obj->getHeight();
                        }) {
    }

    BestAreaFit::BestAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return (shelf->getPackedWidth() + obj->getWidth()) *
                                   max(obj->getHeight(), shelf->getHeight());
                        }) {
    }

    WorstAreaFit::WorstAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const shared_ptr<Shelf> &shelf, const shared_ptr<Item> &obj) {
                            return -(shelf->getPackedWidth() + obj->getWidth()) *
                                   max(obj->getHeight(), shelf->getHeight());
                        }) {
    }
}
