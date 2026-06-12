#pragma once
#include <cstdint>

/**
 * @struct RiffHeader
 * @brief Structure for the RIFF header of the wav file
 */
struct __attribute__((packed)) RiffHeader
{
    char chunkId[4]; // "RIFF" header
    uint32_t chunckSize;
    char format[4]; // "WAVE"
};

/**
 * @struct FmtHeader
 * @brief Structure for the FMT header of the wav file
 */
struct __attribute__((packed)) FmtHeader {
    char chunkId[3]; // "fmt"
    uint32_t chunkSize;
    uint16_t wFormatTag;
    uint16_t wChannels;
    uint32_t dwSamplesPerSec;
    uint32_t dwAvgBytesPerSec;
    uint16_t wBlockAlign;
    uint16_t wBitsPerSample;
};

/**
 * @struct DataHeader
 * @brief Structure for the data header of the wav file
 */
struct __attribute__((packed)) DataHeader {
    char chunkId[4]; // "data"
    uint32_t chunkSize;
};