#ifndef PSN_VECTOR3_H
#define PSN_VECTOR3_H

struct PSNVector3
{
    float x;
    float y;
    float z;

    constexpr PSNVector3()
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    constexpr PSNVector3(
        float x_,
        float y_,
        float z_)
        : x(x_), y(y_), z(z_)
    {
    }

    void set(
        float x_,
        float y_,
        float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};

#endif
