#ifndef PSN_MATH_H
#define PSN_MATH_H

#include <Arduino.h>
#include <math.h>

namespace psn
{
    constexpr float Pi = 3.14159265358979323846f;

    inline float radians(float degrees)
    {
        return degrees * Pi / 180.0f;
    }

    inline float degrees(float radians)
    {
        return radians * 180.0f / Pi;
    }

    inline float clamp(float value, float minimum, float maximum)
    {
        if (value < minimum)
            return minimum;

        if (value > maximum)
            return maximum;

        return value;
    }
}

#endif
