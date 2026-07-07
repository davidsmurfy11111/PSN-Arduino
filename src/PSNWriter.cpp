#include "PSNWriter.h"
#include "PSNWriter.h"

#include <string.h>
PSNWriter::PSNWriter(
    uint8_t* buffer,
    uint16_t capacity)
    :
    m_buffer(buffer),
    m_capacity(capacity),
    m_position(0),
    m_depth(0)
{
}

void PSNWriter::reset()
{
    m_position = 0;
    m_depth = 0;
}

uint8_t* PSNWriter::data() const
{
    return m_buffer;
}

uint16_t PSNWriter::size() const
{
    return m_position;
}

uint16_t PSNWriter::capacity() const
{
    return m_capacity;
}

uint16_t PSNWriter::remaining() const
{
    return m_capacity - m_position;
}

bool PSNWriter::reserve(uint16_t bytes)
{
    return (m_position + bytes) <= m_capacity;
}
bool PSNWriter::writeU8(uint8_t value)
{
    if (!reserve(1))
        return false;

    m_buffer[m_position++] = value;

    return true;
}
bool PSNWriter::writeU16(uint16_t value)
{
    if (!reserve(2))
        return false;

    m_buffer[m_position++] = value & 0xFF;
    m_buffer[m_position++] = (value >> 8) & 0xFF;

    return true;
}
bool PSNWriter::writeU32(uint32_t value)
{
    if (!reserve(4))
        return false;

    m_buffer[m_position++] = value & 0xFF;
    m_buffer[m_position++] = (value >> 8) & 0xFF;
    m_buffer[m_position++] = (value >> 16) & 0xFF;
    m_buffer[m_position++] = (value >> 24) & 0xFF;

    return true;
}
bool PSNWriter::writeU64(uint64_t value)
{
    if (!reserve(8))
        return false;

    for (uint8_t i = 0; i < 8; i++)
    {
        m_buffer[m_position++] = (value >> (i * 8)) & 0xFF;
    }

    return true;
}
bool PSNWriter::writeFloat(float value)
{
    static_assert(sizeof(float) == sizeof(uint32_t),
                  "Unexpected float size");

    uint32_t bits;

    memcpy(&bits, &value, sizeof(bits));

    return writeU32(bits);
}
bool PSNWriter::writeBytes(
    const void* data,
    uint16_t length)
{
    if (!reserve(length))
        return false;

    memcpy(
        &m_buffer[m_position],
        data,
        length);

    m_position += length;

    return true;
}
bool PSNWriter::writeString(
    const char* text)
{
    if (text == nullptr)
        text = "";

    const uint16_t length =
        static_cast<uint16_t>(strlen(text)) + 1;

    return writeBytes(text, length);
}
uint32_t PSNWriter::makeHeader(
    uint16_t id,
    uint16_t length,
    bool hasSubChunks)
{
    uint32_t header =
        static_cast<uint32_t>(id);

    header |=
        (static_cast<uint32_t>(length & 0x7FFF) << 16);

    if (hasSubChunks)
        header |= 0x80000000UL;

    return header;
}
bool PSNWriter::patchU32(
    uint16_t offset,
    uint32_t value)
{
    if ((offset + 4) > m_capacity)
        return false;

    m_buffer[offset + 0] = value & 0xFF;
    m_buffer[offset + 1] = (value >> 8) & 0xFF;
    m_buffer[offset + 2] = (value >> 16) & 0xFF;
    m_buffer[offset + 3] = (value >> 24) & 0xFF;

    return true;
}
bool PSNWriter::beginChunk(
    uint16_t id,
    bool hasSubChunks)
{
    if (m_depth >= MaxDepth)
        return false;

    if (!reserve(4))
        return false;

    Chunk& chunk = m_stack[m_depth++];

    chunk.offset = m_position;
    chunk.id = id;
    chunk.hasSubChunks = hasSubChunks;

    m_position += 4;

    return true;
}
bool PSNWriter::endChunk()
{
    if (m_depth == 0)
        return false;

    Chunk chunk = m_stack[--m_depth];

    uint16_t payloadLength =
        m_position - chunk.offset - 4;

    uint32_t header =
        makeHeader(
            chunk.id,
            payloadLength,
            chunk.hasSubChunks);

    return patchU32(
        chunk.offset,
        header);
}
