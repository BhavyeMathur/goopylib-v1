#include "Bin.h"

namespace gp::packing {
    Bin::Bin(float width, float height, uint32_t page)
            : m_Width(width),
              m_Height(height),
              m_Page(page) {
    }

    const std::vector<Item> &Bin::items() const {
        return m_Items;
    }

    float Bin::width() const {
        return m_Width;
    }

    float Bin::height() const {
        return m_Height;
    }

    uint32_t Bin::page() const {
        return m_Page;
    }

    void Bin::add(gp::packing::Item &item, float x, float y) {
        item.setPage(m_Page);
        item.setPosition(x, y);
        m_Items.push_back(item);
    }
}
