#pragma once

#include "gp.h"
#include "ColorStructs.h"

namespace gp {
    class ColorRGB;

    class ColorHex;

    class ColorCMYK;

    class ColorHSV;

    class ColorHSL;
}


namespace gp {
    class Color {
    public:
        Color(Color const *color);

        Color(const RGB &color, float alpha);

        ~Color();

        Color(int red, int green, int blue, float alpha = 1);

        virtual std::string toString() const;

        int getRed() const;

        void setRed(int red);

        int getGreen() const;

        void setGreen(int red);

        int getBlue() const;

        void setBlue(int red);

        float getAlpha() const;

        void setAlpha(float alpha);

        RGBAf getRGBAf() const;

        // Operator Overloads

        Color operator+(int value) const;

        Color operator+(const Color &value) const;

        Color operator-(int value) const;

        Color operator-(const Color &value) const;

        Color &operator+=(int value);

        Color &operator+=(const Color &value);

        Color &operator-=(int value);

        Color &operator-=(const Color &value);

    protected:
        int m_Red;
        int m_Green;
        int m_Blue;
        float m_Alpha;

        void fromRGB(const RGB &color, float alpha);

        void update();

    private:
        float m_Redf = 0;
        float m_Greenf = 0;
        float m_Bluef = 0;
    };
}

namespace gp {
    class ColorRGB final : public Color {
    public:
        ColorRGB(Color const *color);

        ColorRGB(int red, int green, int blue, float alpha = 1.0f);

    protected:

    private:

    };
}

namespace gp {
    class ColorHex final : public Color {
    public:
        ColorHex(Color const *color);

        ColorHex(const char *hexstring, float alpha = 1.0f);

        std::string toString() const override;

    protected:

    private:
        const char *m_String;
    };
}

namespace gp {
    class ColorCMYK final : public Color {
    public:
        ColorCMYK(Color const *color);

        ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha = 1.0f);

        std::string toString() const override;

        float getCyan() const;

        void setCyan(float value);

        float getMagenta() const;

        void setMagenta(float value);

        float getYellow() const;

        void setYellow(float value);

        float getKey() const;

        void setKey(float value);

    protected:

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}

namespace gp {
    class ColorHSV final : public Color {
    public:
        ColorHSV(Color const *color);

        ColorHSV(int hue, float saturation, float value, float alpha = 1.0f);

        std::string toString() const override;

        int getHue() const;

        void setHue(int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getValue() const;

        void setValue(float value);

    protected:

    private:
        int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}

namespace gp {
    class ColorHSL final : public Color {
    public:
        ColorHSL(Color const *color);

        ColorHSL(int hue, float saturation, float luminance, float alpha = 1.0f);

        std::string toString() const override;

        int getHue() const;

        void setHue(int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getLuminance() const;

        void setLuminance(float value);

    protected:

    private:
        int m_Hue;
        float m_Saturation;
        float m_Luminance;
    };
}

namespace gp {
    std::ostream &operator<<(std::ostream &os, const Color &color);
}
