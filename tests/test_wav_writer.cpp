#include <catch2/catch_test_macros.hpp>
#include "wav_writer.h"
#include "wav_reader.h"
#include <fstream>
#include <filesystem>
#include <cstring>

TEST_CASE("WaveWriter creates a wav file", "[wav_writer]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(50);
    
    for (size_t i = 0; i < 50; ++i) {
        waveform.setSample(i, static_cast<int16_t>(i * 200));
    }
    
    std::string testFile = "test_writer_output.wav";
    
    WavWriter writer;
    writer.write(testFile, waveform);

    REQUIRE(std::filesystem::exists(testFile));
    
    auto fileSize = std::filesystem::file_size(testFile);
    REQUIRE(fileSize == 44 + 50 * 2);
    
    std::filesystem::remove(testFile);
}

TEST_CASE("WaveWriter writes an empty Waveform", "[wav_writer]") {
    Waveform empty(44100, 1, 16);
    
    std::string testFile = "test_writer_empty.wav";
    
    WavWriter writer;
    writer.write(testFile, empty);
    
    REQUIRE(std::filesystem::exists(testFile));

    auto fileSize = std::filesystem::file_size(testFile);
    REQUIRE(fileSize == 44);
    
    std::filesystem::remove(testFile);
}

TEST_CASE("WaveWriter writes headers", "[wav_writer]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    
    std::string testFile = "test_writer_headers.wav";
    
    WavWriter writer;
    writer.write(testFile, waveform);
    
    std::ifstream file(testFile, std::ios::binary);

    // RIFF
    char riffId[4];
    file.read(riffId, 4);
    REQUIRE(std::strncmp(riffId, "RIFF", 4) == 0);
    
    uint32_t riffChunkSize;
    file.read(reinterpret_cast<char*>(&riffChunkSize), 4);
    REQUIRE(riffChunkSize == 100 * 2 + 36);  // dataSize + 36
    
    char waveId[4];
    file.read(waveId, 4);
    REQUIRE(std::strncmp(waveId, "WAVE", 4) == 0);
    
    // FMT
    char fmtId[4];
    file.read(fmtId, 4);
    REQUIRE(std::strncmp(fmtId, "fmt ", 4) == 0);
    
    uint32_t fmtChunkSize;
    file.read(reinterpret_cast<char*>(&fmtChunkSize), 4);
    REQUIRE(fmtChunkSize == 16);
    
    uint16_t formatTag;
    file.read(reinterpret_cast<char*>(&formatTag), 2);
    REQUIRE(formatTag == 1);  // PCM
    
    uint16_t channels;
    file.read(reinterpret_cast<char*>(&channels), 2);
    REQUIRE(channels == 1);
    
    uint32_t sampleRate;
    file.read(reinterpret_cast<char*>(&sampleRate), 4);
    REQUIRE(sampleRate == 44100);
    
    uint32_t avgBytesPerSec;
    file.read(reinterpret_cast<char*>(&avgBytesPerSec), 4);
    REQUIRE(avgBytesPerSec == 88200);  // 44100 * 1 * 2
    
    uint16_t blockAlign;
    file.read(reinterpret_cast<char*>(&blockAlign), 2);
    REQUIRE(blockAlign == 2);
    
    uint16_t bitsPerSample;
    file.read(reinterpret_cast<char*>(&bitsPerSample), 2);
    REQUIRE(bitsPerSample == 16);
    
    // DATA
    char dataId[4];
    file.read(dataId, 4);
    REQUIRE(std::strncmp(dataId, "data", 4) == 0);
    
    uint32_t dataChunkSize;
    file.read(reinterpret_cast<char*>(&dataChunkSize), 4);
    REQUIRE(dataChunkSize == 100 * 2);  // 100 samples * 2 bytes
    
    std::filesystem::remove(testFile);
}