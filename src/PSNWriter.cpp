#include "PSNWriter.h"

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
