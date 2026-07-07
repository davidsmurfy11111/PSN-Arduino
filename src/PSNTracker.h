#ifndef PSN_TRACKER_H
#define PSN_TRACKER_H

#include <Arduino.h>
#include <string.h>

#include "PSNConstants.h"
#include "PSNVector3.h"
#include "PSNQuaternion.h"

class PSNTracker
{
public:

    enum PresentFlags : uint16_t
    {
        HasPosition     = 1 << 0,
        HasVelocity     = 1 << 1,
        HasOrientation  = 1 << 2,
        HasStatus       = 1 << 3,
        HasAcceleration = 1 << 4,
        HasTarget       = 1 << 5
    };

    PSNTracker();

    //------------------------------------------
    // General
    //------------------------------------------

    void clear();

    

    char name[psn::MaxTrackerNameLength];

    //------------------------------------------
    // Data
    //------------------------------------------

    PSNVector3 position;
    PSNVector3 velocity;
    PSNVector3 acceleration;
    PSNVector3 target;

    PSNQuaternion orientation;

    uint32_t status;

    uint16_t presentflags;

    //------------------------------------------
    // Setters
    //------------------------------------------

    PSNTracker& setName(const char* text);

    PSNTracker& setPosition(
        float x,
        float y,
        float z)
    {
        position.set(x, y, z);
        present |= HasPosition;
        return *this;
    }

    PSNTracker& setVelocity(
        float x,
        float y,
        float z)
    {
        velocity.set(x, y, z);
        present |= HasVelocity;
        return *this;
    }

    PSNTracker& setAcceleration(
        float x,
        float y,
        float z)
    {
        acceleration.set(x, y, z);
        present |= HasAcceleration;
        return *this;
    }

    PSNTracker& setTarget(
        float x,
        float y,
        float z)
    {
        target.set(x, y, z);
        present |= HasTarget;
        return *this;
    }

    PSNTracker& setQuaternion(
        float w,
        float x,
        float y,
        float z)
    {
        orientation.w = w;
        orientation.x = x;
        orientation.y = y;
        orientation.z = z;

        present |= HasOrientation;

        return *this;
    }

    PSNTracker& setStatus(uint32_t value)
    {
        status = value;
        present |= HasStatus;
        return *this;
    }

    PSNTracker& setEulerDegrees(
        float roll,
        float pitch,
        float yaw);

};

#endif
