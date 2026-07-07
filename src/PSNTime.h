#ifndef PSN_TIME_H
#define PSN_TIME_H

#include <Arduino.h>

namespace psn
{
    inline uint64_t currentTimeMicros()
    {
        return static_cast<uint64_t>(micros());
    }
}

#endif
