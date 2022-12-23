#pragma once

#include "RenderableObject.h"


namespace gp {
    class Image : public RenderableObject {

        friend class Renderer;

    public:
        Image(Point position, const char *path);

        void resetCenter() final;

        int32_t getWidth() const;

        int32_t getHeight() const;

        const char *getPath() const;

    private:
        ImageVertex m_V1, m_V2, m_V3, m_V4;
        const char *m_Path;

        int32_t m_Width = 0;
        int32_t m_Height = 0;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        void _move(float dx, float dy) final;

        void _rotate(float sin, float cos) final;

        void _scale(float xfactor, float yfactor) final;
    };
}
