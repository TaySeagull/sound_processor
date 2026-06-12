#pragma once
#include <string>
#include "waveform.h"
#include "wave_structures.h"

/**
 * @class WaveReader
 * @brief A class meant to read the wav file
 */
class WaveReader {
public:
    // Constructor
    WaveReader() = default;
    
    // Functions
    Waveform readWavFile(const std::string& filename);

private:
    // Checkers for riff and fmt
    void checkRiffHeader(const RiffHeader& riff);
    void checkFmtHeader(const FmtHeader& fmt);
    void checkDataHeader(const DataHeader& data);
};