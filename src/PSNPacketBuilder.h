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
public:
    bool beginInfoPacket();
    bool beginDataPacket();

private:
    bool writeHeader();

bool PSNPacketBuilder::writeHeader()
{
    if (!m_writer.beginChunk(psn::Header))
        return false;

    if (!m_writer.writeU64(psn::currentTimeMicros()))
        return false;

    return m_writer.endChunk();
}
bool PSNPacketBuilder::beginDataPacket()
{
    m_writer.reset();

    if (!m_writer.beginChunk(psn::DataPacket, true))
        return false;

    if (!writeHeader())
        return false;

    return true;
}
bool PSNPacketBuilder::beginInfoPacket()
{
    m_writer.reset();

    if (!m_writer.beginChunk(psn::InfoPacket, true))
        return false;

    if (!writeHeader())
        return false;

    return true;
}
};

#endif

