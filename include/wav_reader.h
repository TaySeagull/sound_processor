#pragma once
#include <string>
#include "waveform.h"
#include "wave_structures.h"

/**
 * @class WavReader
 * @brief A class to read the wav file
 */
class WavReader {
public:
    WavReader() = default;
    
    Waveform read(const std::string& filename);

private:
    void checkRiffHeader(const RiffHeader& riff);
    void checkFmtHeader(const FmtHeader& fmt);
    void checkDataHeader(const DataHeader& data);
};