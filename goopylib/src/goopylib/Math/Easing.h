#pragma once

#include "pch.h"

namespace gp {
    std::function<float(float)> EaseLinear();

    float inline EasePoly(float t, float power);

    std::function<float(float)> EasePolyIn(float power);

    std::function<float(float)> EasePolyOut(float power);

    std::function<float(float)> EasePolyInOut(float power);

    float inline EaseQuad(float t);

    std::function<float(float)> EaseQuadIn();

    std::function<float(float)> EaseQuadOut();

    std::function<float(float)> EaseQuadInOut();

    float inline EaseCubic(float t);

    std::function<float(float)> EaseCubicIn();

    std::function<float(float)> EaseCubicOut();

    std::function<float(float)> EaseCubicInOut();

    float inline EaseQuart(float t);

    std::function<float(float)> EaseQuartIn();

    std::function<float(float)> EaseQuartOut();

    std::function<float(float)> EaseQuartInOut();

    float inline EaseQuint(float t);

    std::function<float(float)> EaseQuintIn();

    std::function<float(float)> EaseQuintOut();

    std::function<float(float)> EaseQuintInOut();

    float inline EaseCircle(float t);

    std::function<float(float)> EaseCircleIn();

    std::function<float(float)> EaseCircleOut();

    std::function<float(float)> EaseCircleInOut();

    float inline EaseSin(float t);

    std::function<float(float)> EaseSinIn();

    std::function<float(float)> EaseSinOut();

    std::function<float(float)> EaseSinInOut();

    float inline EaseExp(float t, float base);

    std::function<float(float)> EaseExpIn(float base);

    std::function<float(float)> EaseExpOut(float base);

    std::function<float(float)> EaseExpInOut(float base);

    float inline EaseBack(float t, float factor);

    std::function<float(float)> EaseBackIn(float factor);

    std::function<float(float)> EaseBackOut(float factor);

    std::function<float(float)> EaseBackInOut(float factor);

    float inline EaseElastic(float t, int factor);

    std::function<float(float)> EaseElasticIn(int factor);

    std::function<float(float)> EaseElasticOut(int factor);

    std::function<float(float)> EaseElasticInOut(int factor);

    float inline EaseBounce(float t, float damping, int bounces, float scale, const std::vector<float>& zeroes, const std::vector<float>& derivatives);

    std::function<float(float)> EaseBounceIn(int bounces, float damping);

    std::function<float(float)> EaseBounceOut(int bounces, float damping);

    std::function<float(float)> EaseBounceInOut(int bounces, float damping);
}
