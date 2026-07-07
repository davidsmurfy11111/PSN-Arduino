#ifndef PSN_QUATERNION_H
#define PSN_QUATERNION_H

struct PSNQuaternion
{
    float w;
    float x;
    float y;
    float z;

    constexpr PSNQuaternion()
        : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
    {
    }

    constexpr PSNQuaternion(
        float w_,
        float x_,
        float y_,
        float z_)
        : w(w_), x(x_), y(y_), z(z_)
    {
    }
};

#endif
