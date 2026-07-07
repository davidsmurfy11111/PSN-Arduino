#ifndef PSN_PACKET_BUILDER_H
#define PSN_PACKET_BUILDER_H

#include "PSNWriter.h"
#include "PSNTracker.h"

class PSNPacketBuilder
{
public:
    explicit PSNPacketBuilder(PSNWriter& writer);

    void reset();

private:
    PSNWriter& m_writer;
};

#endif
