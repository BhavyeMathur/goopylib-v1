#pragma once

#include "gp.h"


namespace gp {
    class Bitmap {

        friend class Text;

    public:
        ~Bitmap() = default;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

    private:
        float m_Width;
        float m_Height;

        Bitmap(float width, float height);
    };
}
