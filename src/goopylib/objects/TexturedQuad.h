#pragma once

#include "Quad.h"


namespace gp {
    class Bitmap;

    /**
     * An object representing a textured quad with 4 vertices.
     */
    class TexturedQuad : virtual public Quad {

        friend class Renderer;

    public:
        /**
         * An object representing a textured quad with 4 vertices.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         * @param p3 3rd coordinate (x, y) in world space
         * @param p4 4th coordinate (x, y) in world space
         */
        GPAPI TexturedQuad(std::string texture, Point p1, Point p2, Point p3, Point p4);

        /**
         * An object representing a textured quad with 4 vertices.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         * @param p3 3rd coordinate (x, y) in world space
         * @param p4 4th coordinate (x, y) in world space
         */
        GPAPI TexturedQuad(std::string texture, const shared_ptr<Bitmap> &bitmap, Point p1, Point p2, Point p3, Point p4);

        [[nodiscard]] GPAPI std::string toString() const override;

        [[nodiscard]] GPAPI std::string getTextureName() const;

        GPAPI void setBitmap(const shared_ptr<Bitmap> &bitmap);

        [[nodiscard]] GPAPI virtual shared_ptr<Bitmap> getBitmap() const;

    protected:
        TextureVertexAttrib m_T1 = {{0, 1}};
        TextureVertexAttrib m_T2 = {{1, 1}};
        TextureVertexAttrib m_T3 = {{1, 0}};
        TextureVertexAttrib m_T4 = {{0, 0}};

        std::string m_Texture;

        GPAPI TexturedQuad() = default;

        GPAPI TexturedQuad(std::string texture);

        GPAPI TexturedQuad(std::string texture, const shared_ptr<Bitmap> &bitmap);

    private:
        shared_ptr<Bitmap> m_Bitmap = nullptr;

        [[nodiscard]] GPAPI RenderableSubclass _getRenderableSubclass() override;
    };
}
