#ifndef PSN_SENDER_H
#define PSN_SENDER_H

#include <Arduino.h>
#include <EthernetUdp.h>

#include "PSNConstants.h"
#include "PSNTracker.h"
#include "PSNWriter.h"

template <uint8_t MaxTrackers>
class PSNSender
{
public:
    explicit PSNSender(EthernetUDP& udp);

    bool begin(const char* systemName,
               const IPAddress& multicast,
               uint16_t port = psn::DefaultPort);

    PSNTracker& tracker(uint8_t id);

    bool send();

private:
    bool buildInfoPacket();
    bool buildDataPacket();
    bool writeHeader();
    bool writeTracker(uint8_t id);

    EthernetUDP& m_udp;

    IPAddress m_multicast;
    uint16_t  m_port;

    char m_systemName[32];

    PSNTracker m_trackers[MaxTrackers];

    uint8_t m_packet[psn::MaxPacketSize];

    PSNWriter m_writer;

    bool m_infoRequired;
};

#include "PSNSender.tpp"

#endif
