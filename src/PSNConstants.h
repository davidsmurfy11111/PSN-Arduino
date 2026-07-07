#ifndef PSN_CONSTANTS_H
#define PSN_CONSTANTS_H

#include <Arduino.h>

namespace psn
{
    //------------------------------------------
    // Network
    //------------------------------------------

    constexpr uint16_t DefaultPort = 56565;

    //------------------------------------------
    // Packet IDs
    //------------------------------------------

    constexpr uint16_t DataPacket = 0x6755;
    constexpr uint16_t InfoPacket = 0x6756;

    //------------------------------------------
    // Common Chunks
    //------------------------------------------

    constexpr uint16_t Header = 0x0000;

    //------------------------------------------
    // DATA
    //------------------------------------------

    constexpr uint16_t DataTrackerList = 0x0001;

    constexpr uint16_t Position      = 0x0000;
    constexpr uint16_t Speed         = 0x0001;
    constexpr uint16_t Orientation   = 0x0002;
    constexpr uint16_t Status        = 0x0003;
    constexpr uint16_t Acceleration  = 0x0004;
    constexpr uint16_t Target        = 0x0005;

    //------------------------------------------
    // INFO
    //------------------------------------------

    constexpr uint16_t SystemName = 0x0001;
    constexpr uint16_t TrackerList = 0x0002;
    constexpr uint16_t TrackerName = 0x0000;

    //------------------------------------------
    // Limits
    //------------------------------------------

    constexpr uint16_t MaxPacketSize = 1500;

    constexpr uint8_t MaxChunkDepth = 8;
}

#endif
