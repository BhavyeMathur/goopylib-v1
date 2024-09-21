#include "Bin.h"
#include "Item.h"

namespace gp::packing {
    uint32_t Bin::s_Bins = 0;

    Bin::Bin(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Bin::s_Bins) {
        Bin::s_Bins++;
    }

    void Bin::add(Item &item) {
        m_Items.push_back(&item);
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (auto &item: m_Items) {
            sum += item->area();
        }

        return sum / (m_Width * m_Height);
    }

    std::vector<Item *> Bin::items() const {
        std::vector<Item *> copy = m_Items;
        return copy;
    }

    float Bin::getWidth() const {
        return m_Width;
    }

    float Bin::getHeight() const {
        return m_Height;
    }
}
