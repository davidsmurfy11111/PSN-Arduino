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
