#include "Packing.h"

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


// Item Class
namespace gp::packing {
    uint32_t Item::s_Items = 0;

    Item::Item(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Item::s_Items),
              m_LongSide(max(width, height)),
              m_ShortSide(min(width, height)) {
        Item::s_Items++;
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
}

// Bin Class
namespace gp::packing {
    uint32_t Bin::s_Bins = 0;

    Bin::Bin(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Bin::s_Bins) {
        Bin::s_Bins++;
    }

    void Bin::add(const Ref<Item>& item) {
        m_Items.push_back(item);
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (auto &item: m_Items) {
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

// Sorting Algorithms
namespace gp::packing {
    SortingFunction sortByWidth(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getWidth() > item2->getWidth();
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getWidth() < item2->getWidth();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByHeight(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getHeight() > item2->getHeight();
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getHeight() < item2->getHeight();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByPerimeter(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return (item1->getWidth() + item1->getHeight()) >
                                  (item2->getWidth() + item2->getHeight());
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
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
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return (item1->getWidth() * item1->getHeight()) >
                                  (item2->getWidth() * item2->getHeight());
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
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
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return (item1->getWidth() / item1->getHeight()) >
                                  (item2->getWidth() / item2->getHeight());
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
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
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getLongSide() > item2->getLongSide();
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getLongSide() < item2->getLongSide();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }

    SortingFunction sortByShortSide(bool descending) {
        auto compare = descending ?
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getShortSide() > item2->getShortSide();
                       } :
                       [](const Ref<Item>&item1, const Ref<Item>&item2) {
                           return item1->getShortSide() < item2->getShortSide();
                       };

        return [compare](std::vector<Ref<Item>> items) {
            std::sort(items.begin(), items.end(), compare);
            return items;
        };
    }
}

// Packing Algorithm Class
namespace gp::packing {
    PackingAlgorithm::PackingAlgorithm(float binWidth, float binHeight)
            : m_BinWidth(binWidth),
              m_BinHeight(binHeight) {
    }
}
