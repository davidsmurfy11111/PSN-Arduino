#include "PSNTracker.h"

#include <math.h>

PSNTracker::PSNTracker()
{
    

    name[0] = '\0';

    clearFrame();
}
void PSNTracker::clearFrame()
{
    position.set(0.0f,0.0f,0.0f);

    velocity.set(0.0f,0.0f,0.0f);

    acceleration.set(0.0f,0.0f,0.0f);

    target.set(0.0f,0.0f,0.0f);

    orientation.w = 1.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 0.0f;

    status = 0;

    present = 0;
}
PSNTracker&
PSNTracker::setName(const char* text)
{
    if(text == nullptr)
    {
        name[0] = '\0';
        return *this;
    }

    strncpy(
        name,
        text,
        sizeof(name)-1);

    name[sizeof(name)-1] = '\0';

    return *this;
}
PSNTracker&
PSNTracker::setOrientationEuler(
    float roll,
    float pitch,
    float yaw)
{
    roll  *= 0.5f;
    pitch *= 0.5f;
    yaw   *= 0.5f;

    const float cr = cosf(roll);
    const float sr = sinf(roll);

    const float cp = cosf(pitch);
    const float sp = sinf(pitch);

    const float cy = cosf(yaw);
    const float sy = sinf(yaw);

    orientation.w =
        cr*cp*cy +
        sr*sp*sy;

    orientation.x =
        sr*cp*cy -
        cr*sp*sy;

    orientation.y =
        cr*sp*cy +
        sr*cp*sy;

    orientation.z =
        cr*cp*sy -
        sr*sp*cy;

    present |= HasOrientation;

    return *this;
}
