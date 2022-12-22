#pragma once

template<typename T>
    T gcd(T a, T b) {
        return b == 0 ? a : gcd(b, a % b);
    }

template<typename T>
    T distance(T x1, T y1, T x2, T y2) {
        return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    }
