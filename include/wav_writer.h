#pragma once
#include <string>
#include <fstream>
#include "waveform.h"
#include "wave_structures.h"

/**
 * @class WavWriter
 * @brief A class to write wav file
 */
class WavWriter {
public:
    WavWriter() = default;
    
    void write(const std::string& filename, const Waveform& waveform);
    
private:
    RiffHeader createRiffHeader(uint32_t dataSize);
    FmtHeader createFmtHeader(const Waveform& waveform);
    DataHeader createDataHeader(uint32_t dataSize);
};