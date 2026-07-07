#include "PSNPacketBuilder.h"

PSNPacketBuilder::PSNPacketBuilder(PSNWriter& writer)
    : m_writer(writer)
{
}

void PSNPacketBuilder::reset()
{
    m_writer.reset();
}
