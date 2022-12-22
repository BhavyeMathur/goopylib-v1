#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"

namespace gp {
    class RenderableObject {

    public:
        void draw(Window *window);

        void destroy();

        bool isDrawn() const;

        Point getPosition() const;

        void move(float dx, float dy);

        void setPosition(float dx, float dy);

    protected:
        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;

        explicit RenderableObject(Point position);

        void update() const;

    private:
        Point m_Position;
        bool m_Drawn = false;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;

        virtual void _move(float dx, float dy) = 0;
    };
}
