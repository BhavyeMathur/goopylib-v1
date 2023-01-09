#include "Packing.h"

#include <cfloat>
#include <iostream>

#include "src/config.h"

#if (GP_LOG_PACKING != true) and (GP_LOG_PACKING <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_PACKING
#endif

#if !GP_VALUE_CHECK_PACKING
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


// Item Class
namespace gp::packing {
    uint32_t Item::items = 0;

    Item::Item(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Item::items),
              m_LongSide(max(width, height)),
              m_ShortSide(min(width, height)) {
        Item::items++;
    }

    void Item::rotate() {
        float tmp = m_Width;
        m_Width = m_Height;
        m_Height = tmp;

        m_Rotated = !m_Rotated;
    }

    bool Item::isVertical() const {
        return m_Height > m_Width;
    }

    bool Item::isHorizontal() const {
        return m_Width > m_Height;
    }

    bool Item::isRotated() const {
        return m_Rotated;
    }

    float Item::area() const {
        return m_Width * m_Height;
    }

    Point Item::p1() const {
        return {m_X, m_Y};
    }

    Point Item::p2() const {
        return {m_X + m_Width, m_Y + m_Height};
    }

    float Item::getX() const {
        return m_X;
    }

    float Item::getY() const {
        return m_Y;
    }

    float Item::getWidth() const {
        return m_Width;
    }

    float Item::getHeight() const {
        return m_Height;
    }

    float Item::getLongSide() const {
        return m_LongSide;
    }

    float Item::getShortSide() const {
        return m_ShortSide;
    }

    Ref<Item> Item::create(float width, float height) {
        return Ref<Item>(new Item(width, height));
    }
}

// Bin Class
namespace gp::packing {
    uint32_t Bin::bins = 0;

    Bin::Bin(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Bin::bins) {
        Bin::bins++;
    }

    void Bin::add(const Ref<Item> &item) {
        m_Items.push_back(item);
    }

    void Bin::add(Item &item) {
        m_Items.push_back(Ref<Item>(&item));
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (const auto &item: m_Items) {
            sum += item->area();
        }

        return sum / (m_Width * m_Height);
    }

    std::vector<Ref<Item>> Bin::items() const {
        std::vector<Ref<Item>> copy = m_Items;
        return copy;
    }

    float Bin::getWidth() const {
        return m_Width;
    }

    float Bin::getHeight() const {
        return m_Height;
    }
}

// Shelf Class
namespace gp::packing::shelf {
    Shelf::Shelf(float verticalOffset, Bin &bin)
            : m_Bin(bin),
              m_VerticalOffset(verticalOffset),
              m_Width(bin.getWidth()),
              m_AvailableWidth(bin.getWidth()) {

    }

    std::string Shelf::toString() const {
        return strformat("Shelf(offset=%f, packed=%f) with %i items", m_VerticalOffset, m_PackedWidth, m_Items.size());
    }

    bool Shelf::fits(const Ref<Item> &item) const {
        if (m_IsOpen) {
            return item->getWidth() <= m_AvailableWidth and
                   m_VerticalOffset + item->getHeight() <= m_Bin.getHeight();
        }
        else {
            return item->getWidth() <= m_AvailableWidth and item->getHeight() <= m_Height;
        }
    }

    bool Shelf::fitsAbove(const Ref<Item> &item) const {
        return m_VerticalOffset + m_Height + item->getHeight() <= m_Bin.getHeight();
    }

    void Shelf::add(const Ref<Item> &item) {
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

    std::ostream &operator<<(std::ostream &os, const Shelf &shelf) {
        os << shelf.toString();
        return os;
    }
}

// Shelved Bin Class
namespace gp::packing {
    ShelvedBin::ShelvedBin(float width, float height)
            : Bin(width, height),
              m_OpenShelf(Ref<shelf::Shelf>(new shelf::Shelf(0, *this))) {
        m_Shelves.push_back(m_OpenShelf);
    }

    Ref<shelf::Shelf> ShelvedBin::addShelf() {
        m_OpenShelf->close();
        m_OpenShelf = Ref<shelf::Shelf>(new shelf::Shelf(m_OpenShelf->m_VerticalOffset + m_OpenShelf->m_Height, *this));
        m_Shelves.push_back(m_OpenShelf);

        return m_OpenShelf;
    }

    float ShelvedBin::packingRatio() const {
        if (m_ID == Bin::bins - 1) { // this is the latest bin
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

    std::vector<Ref<shelf::Shelf>>::const_iterator ShelvedBin::begin() const {
        return m_Shelves.begin();
    }

    std::vector<Ref<shelf::Shelf>>::const_iterator ShelvedBin::end() const {
        return m_Shelves.end();
    }
}

// Sorting Algorithms
namespace gp::packing {
    SortingFunction sortByWidth(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getWidth() > item2->getWidth();
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getWidth() < item2->getWidth();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByHeight(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getHeight() > item2->getHeight();
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getHeight() < item2->getHeight();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByPerimeter(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() + item1->getHeight()) >
                                  (item2->getWidth() + item2->getHeight());
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() + item1->getHeight()) <
                                  (item2->getWidth() + item2->getHeight());
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByArea(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() * item1->getHeight()) >
                                  (item2->getWidth() * item2->getHeight());
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() * item1->getHeight()) <
                                  (item2->getWidth() * item2->getHeight());
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortBySideRatio(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() / item1->getHeight()) >
                                  (item2->getWidth() / item2->getHeight());
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return (item1->getWidth() / item1->getHeight()) <
                                  (item2->getWidth() / item2->getHeight());
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByLongSide(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getLongSide() > item2->getLongSide();
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getLongSide() < item2->getLongSide();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByShortSide(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getShortSide() > item2->getShortSide();
                       } :
                       [](const Ref<Item> &item1, const Ref<Item> &item2) {
                           return item1->getShortSide() < item2->getShortSide();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }
}

// Shelf Packing Algorithms
namespace gp::packing {
    std::vector<Ref<ShelvedBin>> shelf::packNextFit(std::vector<Ref<Item>> &items,
                                                    float binWidth,
                                                    float binHeight,
                                                    const SortingFunction &sorting,
                                                    bool allowRotation) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};
        Ref<Shelf> shelf = bins.back()->m_OpenShelf;

        for (const auto &item: items) {
            if (allowRotation and (item->isVertical() != (item->getLongSide() <= shelf->getHeight()))) {
                item->rotate();
            }

            if (shelf->fits(item)) {
                shelf->add(item);
                continue;
            }

            if (shelf->fitsAbove(item)) {
                shelf = bins.back()->addShelf();
            }
            else {
                bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
                shelf = bins.back()->m_OpenShelf;
            }

            if (allowRotation and item->isVertical()) {
                item->rotate();
            }
            shelf->add(item);
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packFirstFit(std::vector<Ref<Item>> &items,
                                                     float binWidth,
                                                     float binHeight,
                                                     const SortingFunction &sorting,
                                                     bool allowRotation) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};

        for (const auto &item: items) {
            for (const auto &bin: bins) {
                for (const auto &shelf: *bin) {
                    if (allowRotation and (item->isVertical() != (item->getLongSide() <= shelf->getHeight()))) {
                        item->rotate();
                    }

                    if (shelf->fits(item)) {
                        shelf->add(item);
                        goto next_item;
                    }
                }

                if (bin->m_OpenShelf->fitsAbove(item)) {
                    if (allowRotation and item->isVertical()) {
                        item->rotate();
                    }
                    bin->addShelf()->add(item);
                    goto next_item;
                }
            }
            {
                // code only reaches here if item has not been added to a shelf
                bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));

                if (allowRotation and item->isVertical()) {
                    item->rotate();
                }
                const auto &newBin = bins.back();
                const auto &newShelf = newBin->m_OpenShelf;
                newShelf->add(item);
            }

            next_item:
            continue;
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packScoredFit(std::vector<Ref<Item>> &items,
                                                      float binWidth,
                                                      float binHeight,
                                                      const ScoringFunction &scoringFunction,
                                                      const SortingFunction &sorting,
                                                      bool allowRotation) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};

        for (const auto &item: items) {
            Ref<Shelf> bestShelf = nullptr;
            float bestScore = -FLT_MAX;
            bool bestOrientation = false;  // un-rotated

            for (const auto &bin: bins) {
                for (const auto &shelf: *bin) {
                    if (allowRotation and (item->isVertical() != (item->getLongSide() <= shelf->getHeight()))) {
                        item->rotate();
                    }

                    if (shelf->fits(item)) {
                        float score = scoringFunction(shelf, item);
                        if (score > bestScore) {
                            bestShelf = shelf;
                            bestScore = score;
                            bestOrientation = item->isRotated();
                        }
                    }
                }

                if (bestShelf == nullptr and bin->m_OpenShelf->fitsAbove(item)) {
                    auto shelf = bin->addShelf();

                    float score = scoringFunction(shelf, item);
                    if (score > bestScore) {
                        bestShelf = shelf;
                        bestScore = score;
                        bestOrientation = item->isRotated();
                    }
                }
            }

            if (bestShelf == nullptr) {
                bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));

                if (allowRotation and item->isVertical()) {
                    item->rotate();
                }

                bestShelf = bins.back()->m_OpenShelf;
                bestOrientation = item->isRotated();
            }

            if (item->isRotated() != bestOrientation) {
                item->rotate();
            }
            bestShelf->add(item);
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packBestWidthFit(std::vector<Ref<Item>> &items,
                                                         float binWidth,
                                                         float binHeight,
                                                         const SortingFunction &sorting,
                                                         bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return obj->getWidth() - shelf->getAvailableWidth();
                             }, sorting, allowRotation);
    }

    std::vector<Ref<ShelvedBin>> shelf::packWorstWidthFit(std::vector<Ref<Item>> &items,
                                                          float binWidth,
                                                          float binHeight,
                                                          const SortingFunction &sorting,
                                                          bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return shelf->getAvailableWidth() - obj->getWidth();
                             }, sorting, allowRotation);
    }

    std::vector<Ref<ShelvedBin>> shelf::packBestHeightFit(std::vector<Ref<Item>> &items,
                                                          float binWidth,
                                                          float binHeight,
                                                          const SortingFunction &sorting,
                                                          bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return obj->getHeight() - shelf->getHeight();
                             }, sorting, allowRotation);
    }

    std::vector<Ref<ShelvedBin>> shelf::packWorstHeightFit(std::vector<Ref<Item>> &items,
                                                           float binWidth,
                                                           float binHeight,
                                                           const SortingFunction &sorting,
                                                           bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return shelf->getHeight() - obj->getHeight();
                             }, sorting, allowRotation);
    }

    std::vector<Ref<ShelvedBin>> shelf::packBestAreaFit(std::vector<Ref<Item>> &items,
                                                        float binWidth,
                                                        float binHeight,
                                                        const SortingFunction &sorting,
                                                        bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return (shelf->getPackedWidth() + obj->getWidth()) *
                                        max(obj->getHeight(), shelf->getHeight());
                             }, sorting, allowRotation);
    }

    std::vector<Ref<ShelvedBin>> shelf::packWorstAreaFit(std::vector<Ref<Item>> &items,
                                                         float binWidth,
                                                         float binHeight,
                                                         const SortingFunction &sorting,
                                                         bool allowRotation) {
        return packScoredFit(items, binWidth, binHeight,
                             [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                 return -(shelf->getPackedWidth() + obj->getWidth()) *
                                        max(obj->getHeight(), shelf->getHeight());
                             }, sorting, allowRotation);
    }
}

// Oriented Shelf Packing Algorithms
namespace gp::packing {
    std::vector<Ref<ShelvedBin>> shelf::packOrientedNextFit(std::vector<Ref<Item>> &items,
                                                            float binWidth,
                                                            float binHeight,
                                                            const SortingFunction &sorting,
                                                            bool orientVertically) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};
        Ref<Shelf> shelf = bins.back()->m_OpenShelf;

        for (const auto &item: items) {
            if (orientVertically == item->isHorizontal()) {
                item->rotate();
            }

            if (shelf->fits(item)) {
                shelf->add(item);
                continue;
            }

            if (shelf->fitsAbove(item)) {
                shelf = bins.back()->addShelf();
            }
            else {
                bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
                shelf = bins.back()->m_OpenShelf;
            }

            shelf->add(item);
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedFirstFit(std::vector<Ref<Item>> &items,
                                                             float binWidth,
                                                             float binHeight,
                                                             const SortingFunction &sorting,
                                                             bool orientVertically) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};

        for (const auto &item: items) {
            if (orientVertically == item->isHorizontal()) {
                item->rotate();
            }

            for (const auto &bin: bins) {
                for (const auto &shelf: *bin) {
                    if (shelf->fits(item)) {
                        shelf->add(item);
                        goto next_item;
                    }
                }

                if (bin->m_OpenShelf->fitsAbove(item)) {
                    bin->addShelf()->add(item);
                    goto next_item;
                }
            }

            // code only reaches here if item has not been added to a shelf
            bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
            bins.back()->m_OpenShelf->add(item);

            next_item:
            continue;
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedScoredFit(std::vector<Ref<Item>> &items,
                                                              float binWidth,
                                                              float binHeight,
                                                              const ScoringFunction &scoringFunction,
                                                              const SortingFunction &sorting,
                                                              bool orientVertically) {
        if (sorting) {
            items = sorting(items);
        }

        std::vector<Ref<ShelvedBin>> bins = {Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight))};

        for (const auto &item: items) {
            if (orientVertically == item->isHorizontal()) {
                item->rotate();
            }

            Ref<Shelf> bestShelf = nullptr;
            float bestScore = -FLT_MAX;

            for (const auto &bin: bins) {
                for (const auto &shelf: *bin) {
                    if (shelf->fits(item)) {
                        float score = scoringFunction(shelf, item);
                        if (score > bestScore) {
                            bestShelf = shelf;
                            bestScore = score;
                        }
                    }
                }

                if (bestShelf == nullptr and bin->m_OpenShelf->fitsAbove(item)) {
                    auto shelf = bin->addShelf();

                    float score = scoringFunction(shelf, item);
                    if (score > bestScore) {
                        bestShelf = shelf;
                        bestScore = score;
                    }
                }
            }

            if (bestShelf == nullptr) {
                bins.push_back(Ref<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
                bestShelf = bins.back()->m_OpenShelf;
            }

            bestShelf->add(item);
        }

        return bins;
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedBestWidthFit(std::vector<Ref<Item>> &items,
                                                                 float binWidth,
                                                                 float binHeight,
                                                                 const SortingFunction &sorting,
                                                                 bool orientVertically) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return obj->getWidth() - shelf->getAvailableWidth();
                                     }, sorting, orientVertically);
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedWorstWidthFit(std::vector<Ref<Item>> &items,
                                                                  float binWidth,
                                                                  float binHeight,
                                                                  const SortingFunction &sorting,
                                                                  bool orientVertically) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return shelf->getAvailableWidth() - obj->getWidth();
                                     }, sorting, orientVertically);
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedBestHeightFit(std::vector<Ref<Item>> &items,
                                                                  float binWidth,
                                                                  float binHeight,
                                                                  const SortingFunction &sorting,
                                                                  bool orientVertically) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return obj->getHeight() - shelf->getHeight();
                                     }, sorting, orientVertically);
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedWorstHeightFit(std::vector<Ref<Item>> &items,
                                                                   float binWidth,
                                                                   float binHeight,
                                                                   const SortingFunction &sorting,
                                                                   bool orientVertically) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return shelf->getHeight() - obj->getHeight();
                                     }, sorting, orientVertically);
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedBestAreaFit(std::vector<Ref<Item>> &items,
                                                                float binWidth,
                                                                float binHeight,
                                                                const SortingFunction &sorting,
                                                                bool orientVertically) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return (shelf->getPackedWidth() + obj->getWidth()) *
                                                max(obj->getHeight(), shelf->getHeight());
                                     }, sorting, orientVertically);
    }

    std::vector<Ref<ShelvedBin>> shelf::packOrientedWorstAreaFit(std::vector<Ref<Item>> &items,
                                                                 float binWidth,
                                                                 float binHeight,
                                                                 const SortingFunction &sorting,
                                                                 bool allowRotation) {
        return packOrientedScoredFit(items, binWidth, binHeight,
                                     [](const Ref<Shelf> &shelf, const Ref<Item> &obj) {
                                         return -(shelf->getPackedWidth() + obj->getWidth()) *
                                                max(obj->getHeight(), shelf->getHeight());
                                     }, sorting, allowRotation);
    }
}
