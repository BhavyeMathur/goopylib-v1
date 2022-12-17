#include "pch.h"

#define EASE_IN(func, ...) func(t, ##__VA_ARGS__)
#define EASE_OUT(func, ...) 1 - func(1 - t, ##__VA_ARGS__)
#define EASE_INOUT(func, ...) t < 0.5 ? func(2 * t, ##__VA_ARGS__) / 2 : 1 - func(2 * (1 - t), ##__VA_ARGS__) / 2

namespace {
    void ProcessEaseBounce(int bounces, float *damping, float *scale, std::vector<float> &zeroes,
                           std::vector<float> &derivatives) {
        *damping = -sqrt(*damping);
        zeroes.push_back(1);
        derivatives.push_back(-2);

        zeroes.push_back(-2 * *damping + 1);
        derivatives.push_back(2 * (zeroes[0] - zeroes[1]) + *damping * derivatives[0]);

        for (int i = 2; i < bounces; i++) {
            zeroes.push_back(*damping * (zeroes[i - 2] - zeroes[i - 1]) + zeroes[i - 1]);
            derivatives.push_back(2 * (zeroes[i - 1] - zeroes[i]) + *damping * derivatives[i - 1]);
        }

        *scale = zeroes[bounces - 1];
    }
}

namespace gp {
    std::function<float(float)> EaseLinear() {
        return [](float t) {
            return t;
        };
    }

    float inline EasePoly(float t, float power) {
        return pow(t, power);
    }

    std::function<float(float)> EasePolyIn(float power) {
        return [power](float t) {
            return EASE_IN(EasePoly, power);
        };
    }

    std::function<float(float)> EasePolyOut(float power) {
        return [power](float t) {
            return EASE_OUT(EasePoly, power);
        };
    }

    std::function<float(float)> EasePolyInOut(float power) {
        return [power](float t) {
            return EASE_INOUT(EasePoly, power);
        };
    }

    float inline EaseQuad(float t) {
        return t * t;
    }

    std::function<float(float)> EaseQuadIn() {
        return [](float t) {
            return EASE_IN(EaseQuad);
        };
    }

    std::function<float(float)> EaseQuadOut() {
        return [](float t) {
            return EASE_OUT(EaseQuad);
        };
    }

    std::function<float(float)> EaseQuadInOut() {
        return [](float t) {
            return EASE_INOUT(EaseQuad);
        };
    }

    float inline EaseCubic(float t) {
        return t * t * t;
    }

    std::function<float(float)> EaseCubicIn() {
        return [](float t) {
            return EASE_IN(EaseCubic);
        };
    }

    std::function<float(float)> EaseCubicOut() {
        return [](float t) {
            return EASE_OUT(EaseCubic);
        };
    }

    std::function<float(float)> EaseCubicInOut() {
        return [](float t) {
            return EASE_INOUT(EaseCubic);
        };
    }

    float inline EaseQuart(float t) {
        return t * t * t * t;
    }

    std::function<float(float)> EaseQuartIn() {
        return [](float t) {
            return EASE_IN(EaseQuart);
        };
    }

    std::function<float(float)> EaseQuartOut() {
        return [](float t) {
            return EASE_OUT(EaseQuart);
        };
    }

    std::function<float(float)> EaseQuartInOut() {
        return [](float t) {
            return EASE_INOUT(EaseQuart);
        };
    }

    float inline EaseQuint(float t) {
        return t * t * t * t * t;
    }

    std::function<float(float)> EaseQuintIn() {
        return [](float t) {
            return EASE_IN(EaseQuint);
        };
    }

    std::function<float(float)> EaseQuintOut() {
        return [](float t) {
            return EASE_OUT(EaseQuint);
        };
    }

    std::function<float(float)> EaseQuintInOut() {
        return [](float t) {
            return EASE_INOUT(EaseQuint);
        };
    }

    float inline EaseCircle(float t) {
        return 1 - sqrt(1 - (float) pow(t, 2));
    }

    std::function<float(float)> EaseCircleIn() {
        return [](float t) {
            return EASE_IN(EaseCircle);
        };
    }

    std::function<float(float)> EaseCircleOut() {
        return [](float t) {
            return EASE_OUT(EaseCircle);
        };
    }

    std::function<float(float)> EaseCircleInOut() {
        return [](float t) {
            return EASE_INOUT(EaseCircle);
        };
    }

    float inline EaseSin(float t) {
        return 1 - (float) cos(t * 1.57079632679);
    }

    std::function<float(float)> EaseSinIn() {
        return [](float t) {
            return EASE_IN(EaseSin);
        };
    }

    std::function<float(float)> EaseSinOut() {
        return [](float t) {
            return EASE_OUT(EaseSin);
        };
    }

    std::function<float(float)> EaseSinInOut() {
        return [](float t) {
            return EASE_INOUT(EaseSin);
        };
    }

    float inline EaseExp(float t, float base) {
        return pow(base, 10 * t - 10);
    }

    std::function<float(float)> EaseExpIn(float base) {
        return [base](float t) {
            return EASE_IN(EaseExp, base);
        };
    }

    std::function<float(float)> EaseExpOut(float base) {
        return [base](float t) {
            return EASE_OUT(EaseExp, base);
        };
    }

    std::function<float(float)> EaseExpInOut(float base) {
        return [base](float t) {
            return EASE_INOUT(EaseExp, base);
        };
    }

    float inline EaseBack(float t, float factor) {
        return ((factor + 1) * t * t * t - factor * t * t);
    }

    std::function<float(float)> EaseBackIn(float factor) {
        return [factor](float t) {
            return EASE_IN(EaseBack, factor);
        };
    }

    std::function<float(float)> EaseBackOut(float factor) {
        return [factor](float t) {
            return EASE_OUT(EaseBack, factor);
        };
    }

    std::function<float(float)> EaseBackInOut(float factor) {
        return [factor](float t) {
            return EASE_INOUT(EaseBack, factor);
        };
    }

    float inline EaseElastic(float t, int factor) {
        return (float) pow(2, 10 * (t - 1)) * (float) std::sin(1.5707963267 * t * (1 + 4 * factor));
    }

    std::function<float(float)> EaseElasticIn(int factor) {
        return [factor](float t) {
            return EASE_IN(EaseElastic, factor);
        };
    }

    std::function<float(float)> EaseElasticOut(int factor) {
        return [factor](float t) {
            return EASE_OUT(EaseElastic, factor);
        };
    }

    std::function<float(float)> EaseElasticInOut(int factor) {
        return [factor](float t) {
            return EASE_INOUT(EaseElastic, factor);
        };
    }

    float inline EaseBounce(float t, float damping, int bounces, float scale, const std::vector<float> &zeroes,
                            const std::vector<float> &derivatives) {
        t = scale * (1 - t);
        for (int i = 0; i < bounces; i++) {
            if (zeroes[i] >= t) {
                if (i == 0) {
                    return -t * t + 1;
                }
                else {
                    t -= zeroes[i - 1];
                    return -t * t + damping * t * derivatives[i - 1];
                }
            }
        }
        return 1;
    }

    std::function<float(float)> EaseBounceIn(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        ProcessEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_IN(EaseBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> EaseBounceOut(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        ProcessEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_OUT(EaseBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> EaseBounceInOut(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        ProcessEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_INOUT(EaseBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }
}
