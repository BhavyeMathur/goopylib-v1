#pragma once

#include "gp.h"
#include <functional>

namespace gp {
    std::function<float(float)> easeLinear();

    float easePoly(float t, float power);

    std::function<float(float)> easePolyIn(float power);

    std::function<float(float)> easePolyOut(float power);

    std::function<float(float)> easePolyInOut(float power);

    float easeQuad(float t);

    std::function<float(float)> easeQuadIn();

    std::function<float(float)> easeQuadOut();

    std::function<float(float)> easeQuadInOut();

    float easeCubic(float t);

    std::function<float(float)> easeCubicIn();

    std::function<float(float)> easeCubicOut();

    std::function<float(float)> easeCubicInOut();

    float easeQuart(float t);

    std::function<float(float)> easeQuartIn();

    std::function<float(float)> easeQuartOut();

    std::function<float(float)> easeQuartInOut();

    float easeQuint(float t);

    std::function<float(float)> easeQuintIn();

    std::function<float(float)> easeQuintOut();

    std::function<float(float)> easeQuintInOut();

    float easeCircle(float t);

    std::function<float(float)> easeCircleIn();

    std::function<float(float)> easeCircleOut();

    std::function<float(float)> easeCircleInOut();

    float easeSin(float t);

    std::function<float(float)> easeSinIn();

    std::function<float(float)> easeSinOut();

    std::function<float(float)> easeSinInOut();

    float easeExp(float t, float base);

    std::function<float(float)> easeExpIn(float base);

    std::function<float(float)> easeExpOut(float base);

    std::function<float(float)> easeExpInOut(float base);

    float easeBack(float t, float factor);

    std::function<float(float)> easeBackIn(float factor);

    std::function<float(float)> easeBackOut(float factor);

    std::function<float(float)> easeBackInOut(float factor);

    float easeElastic(float t, int factor);

    std::function<float(float)> easeElasticIn(int factor);

    std::function<float(float)> easeElasticOut(int factor);

    std::function<float(float)> easeElasticInOut(int factor);

    float easeBounce(float t, float damping, int bounces, float scale, const std::vector<float> &zeroes,
                            const std::vector<float> &derivatives);

    std::function<float(float)> easeBounceIn(int bounces, float damping);

    std::function<float(float)> easeBounceOut(int bounces, float damping);

    std::function<float(float)> easeBounceInOut(int bounces, float damping);

    std::function<float(float)> combineEasing(const std::function<float(float)> &func1,
                                              const std::function<float(float)> &func2);
}
