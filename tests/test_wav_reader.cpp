#include <catch2/catch_test_macros.hpp>
#include "wav_reader.h"
#include "wav_writer.h"
#include <fstream>
#include <filesystem>

TEST_CASE("WaveReader reads wav file", "[wav_reader]") {
    Waveform original(44100, 1, 16);
    original.resize(100);
    
    for (size_t i = 0; i < 100; ++i) {
        original.setSample(i, static_cast<int16_t>(i * 100));
    }
    
    std::string testFile = "test_reader_input.wav";

    WavWriter writer;
    writer.write(testFile, original);
    
    WavReader reader;
    Waveform loaded = reader.read(testFile);
    
    REQUIRE(loaded.getSampleRate() == 44100);
    REQUIRE(loaded.getChannels() == 1);
    REQUIRE(loaded.getBitsPerSample() == 16);
    REQUIRE(loaded.getNumSamples() == 100);
    
    for (size_t i = 0; i < 100; ++i) {
        REQUIRE(loaded.getSample(i) == original.getSample(i));
    }
    
    std::filesystem::remove(testFile);
}

TEST_CASE("WaveReader reads empty wav file", "[wav_reader]") {
    Waveform empty(44100, 1, 16);
    std::string testFile = "test_reader_empty.wav";
    
    WavWriter writer;
    writer.write(testFile, empty);
    
    WavReader reader;
    Waveform loaded = reader.read(testFile);
    
    REQUIRE(loaded.getNumSamples() == 0);
    
    std::filesystem::remove(testFile);
}


TEST_CASE("WaveReader reads wav file with different samples", "[wav_reader]") {
    Waveform original(44100, 1, 16);
    original.resize(4);

    original.setSample(0, 0); 
    original.setSample(1, 32767);
    original.setSample(2, -32768);
    original.setSample(3, 1000);
    
    std::string testFile = "test_reader_diff.wav";
    WavWriter writer;
    writer.write(testFile, original);
    
    WavReader reader;
    Waveform loaded = reader.read(testFile);
    
    REQUIRE(loaded.getNumSamples() == 4);
    for (size_t i = 0; i < 4; ++i) {
        REQUIRE(loaded.getSample(i) == original.getSample(i));
    }
    
    std::filesystem::remove(testFile);
}