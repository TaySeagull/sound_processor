#include <cstring>
#include <stdexcept>
#include <fstream>
#include "wav_reader.h"
#include "waveform.h"

/**
 * @brief Reads a wav file
 * @details Tries to read wav file and chechs its sections
 * RIFF, FMT and DATA based on the task's requirements
 * @param std::string& filename
 */
Waveform WavReader::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }

    RiffHeader riffHeader;
    file.read(reinterpret_cast<char*>(&riffHeader), sizeof(RiffHeader));
    
    if (!file.good()) {
        throw std::runtime_error("Failed to read RIFF header from " + filename);
    }

    checkRiffHeader(riffHeader);

    FmtHeader fmtHeader;
    file.read(reinterpret_cast<char*>(&fmtHeader), sizeof(FmtHeader));
    
    if (!file.good()) {
        throw std::runtime_error("Failed to read fmt header from " + filename);
    }

    checkFmtHeader(fmtHeader);

    DataHeader dataHeader;
    file.read(reinterpret_cast<char*>(&dataHeader), sizeof(DataHeader));
    
    if (!file.good()) {
        throw std::runtime_error("Failed to read data header from " + filename);
    }

    checkDataHeader(dataHeader);

    uint32_t numberSamples = dataHeader.chunkSize / sizeof(int16_t);

    Waveform waveform(
        fmtHeader.dwSamplesPerSec,
        fmtHeader.wChannels,
        fmtHeader.wBitsPerSample
    );
    
    if (numberSamples > 0) {
        waveform.resize(numberSamples);

        file.read(
            reinterpret_cast<char*>(waveform.getSamples().data()),
            dataHeader.chunkSize
        );
        
        if (!file.good()) {
            throw std::runtime_error("Failed to read samples from " + filename);
        }
    }

    return waveform;
}

/**
 * @brief Checks RIFF header
 * @details Checks RIFF header and WAVE format and throws error in stderr
 * @param riff const RiffHeader&
 */
void WavReader::checkRiffHeader(const RiffHeader& riff)
{
    if (std::strncmp(riff.chunkId, "RIFF", 4) != 0)
    {throw std::runtime_error("Failed RIFF chunck");}

    if (std::strncmp(riff.format, "WAVE", 4) != 0) {
        throw std::runtime_error("Failed WAVE format");
    }
}

/**
 * @brief Checks FMT header
 * @details Checks FMT header, format tag PCM, number of channels, sample rate,
 * samples per seconds and bits per sample and throws error in stderr
 * Tasks requirement:
 *      - fomat taf: PCM
 *      - number of channels: 1
 *      - sample rate: 44100 Hz
 *      - bits per sample: 16
 * @param riff const FmtHeader&
 */
void WavReader::checkFmtHeader(const FmtHeader& fmt)
{
    if (std::strncmp(fmt.chunkId, "fmt", 3) != 0)
    { throw std::runtime_error("Failed FMT chunck");}

    if (fmt.wFormatTag != 1) {
        throw std::runtime_error("Only PCM format is supported");
    }

    if (fmt.wChannels != 1) {
        throw std::runtime_error("Only mono (1 channel) audio is supported");
    }

    if (fmt.dwSamplesPerSec != 44100) {
        throw std::runtime_error("Only 44100 Hz sample rate is supported");
    }

    if (fmt.wBitsPerSample != 16) {
        throw std::runtime_error("Only 16 bit samples are supported");
    }
}

/**
 * @brief Checks DATA header
 * @details Checks DATA header
 * @param riff const DataHeader&
 */
void WavReader::checkDataHeader(const DataHeader& data)
{
    if (std::strncmp(data.chunkId, "data", 4) != 0) {
        throw std::runtime_error("Invalid data header");
    }
}