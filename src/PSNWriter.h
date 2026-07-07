#ifndef PSN_WRITER_H
#define PSN_WRITER_H

#include <Arduino.h>
#include "PSNConstants.h"

class PSNWriter
{
public:

    explicit PSNWriter(
        uint8_t* buffer,
        uint16_t capacity);

    //------------------------------------------
    // Buffer Management
    //------------------------------------------

    void reset();

    uint8_t* data() const;

    uint16_t size() const;

    uint16_t capacity() const;

    uint16_t remaining() const;

    //------------------------------------------
    // Chunk Handling
    //------------------------------------------

    bool beginChunk(
        uint16_t id,
        bool hasSubChunks = false);

    bool endChunk();

    //------------------------------------------
    // Primitive Writers
    //------------------------------------------

    bool writeU8(uint8_t value);

    bool writeU16(uint16_t value);

    bool writeU32(uint32_t value);

    bool writeU64(uint64_t value);

    bool writeFloat(float value);

    bool writeBytes(
        const void* data,
        uint16_t length);

    bool writeString(
        const char* text);

private:

    struct Chunk
    {
        uint16_t offset;
        uint16_t id;
        bool hasSubChunks;
    };

    static constexpr uint8_t MaxDepth = 8;

    uint8_t* m_buffer;
    uint16_t m_capacity;
    uint16_t m_position;

    Chunk m_stack[MaxDepth];
    uint8_t m_depth;

    bool reserve(uint16_t bytes);

    bool patchU32(
        uint16_t offset,
        uint32_t value);

    uint32_t makeHeader(
        uint16_t id,
        uint16_t length,
        bool hasSubChunks);
};

#endif
