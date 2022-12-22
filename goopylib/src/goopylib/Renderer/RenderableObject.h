#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"

namespace gp {
    class RenderableObject {

    public:
        void draw(Window *window);

        void destroy();

        bool isDrawn() const {
            return m_Drawn;
        }

        virtual void move(float dx, float dy) = 0;

        virtual void setPosition(float dx, float dy) = 0;

        Point getPosition() const {
            return m_Position;
        };

    protected:
        Point m_Position;

        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;
        bool m_Drawn = false;

        explicit RenderableObject(Point position)
                : m_Position(position) {
        }

    private:

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;
    };
}
