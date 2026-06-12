#include "wav_writer.h"
#include <stdexcept>
#include <cstring>

/**
 * @brief Writes a Waveform object to a wav file
 * @param filename filename
 * @param waveform The Waveform object containing audio data to write
 */
void WavWriter::write(const std::string& filename, const Waveform& waveform) {
    std::ofstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    uint32_t dataSize = waveform.getNumSamples() * sizeof(int16_t);
    
    RiffHeader riff = createRiffHeader(dataSize);
    FmtHeader fmt = createFmtHeader(waveform);
    DataHeader data = createDataHeader(dataSize);
    
    file.write(reinterpret_cast<const char*>(&riff), sizeof(RiffHeader));
    file.write(reinterpret_cast<const char*>(&fmt), sizeof(FmtHeader));
    file.write(reinterpret_cast<const char*>(&data), sizeof(DataHeader));
    
    file.write(reinterpret_cast<const char*>(waveform.getSamples().data()), dataSize);
    
    if (!file.good()) {
        throw std::runtime_error("Error writing to file" + filename);
    }
}

/**
 * @brief Creates the RIFF header
 * @param dataSize Size of the audio data in bytes
 * @return RiffHeader structure
 */
RiffHeader WavWriter::createRiffHeader(uint32_t dataSize) {
    RiffHeader riff;
    std::memcpy(riff.chunkId, "RIFF", 4);
    riff.chunckSize = dataSize + 36;  // 36 = fmt + data
    std::memcpy(riff.format, "WAVE", 4);
    return riff;
}

/**
 * @brief Creates the FMT header
 * @param waveform The Waveform object containing audio data to write
 * @return FmtHeader structure
 */
FmtHeader WavWriter::createFmtHeader(const Waveform& waveform) {
    FmtHeader fmt;
    std::memcpy(fmt.chunkId, "fmt ", 4);
    fmt.chunkSize = 16;
    fmt.wFormatTag = 1;
    fmt.wChannels = waveform.getChannels();
    fmt.dwSamplesPerSec = waveform.getSampleRate();
    fmt.dwAvgBytesPerSec = waveform.getSampleRate() * waveform.getChannels() * (waveform.getBitsPerSample() / 8);
    fmt.wBlockAlign = waveform.getChannels() * (waveform.getBitsPerSample() / 8);
    fmt.wBitsPerSample = waveform.getBitsPerSample();
    return fmt;
}

/**
 * @brief Creates the DATA header
 * @param dataSize Size of the audio data in bytes
 * @return DataHeader structure
 */
DataHeader WavWriter::createDataHeader(uint32_t dataSize) {
    DataHeader chunck;
    std::memcpy(chunck.chunkId, "data", 4);
    chunck.chunkSize = dataSize;
    return chunck;
}