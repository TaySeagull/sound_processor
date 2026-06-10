#include <catch2/catch_test_macros.hpp>
#include "waveform.h"

TEST_CASE("Base waveform", "[waveform]") {
    Waveform waveform;
    
    REQUIRE(waveform.getSampleRate() == 44100);
    REQUIRE(waveform.getChannels() == 1);
    REQUIRE(waveform.getBitsPerSample() == 16);
    REQUIRE(waveform.getNumSamples() == 0);
}

TEST_CASE("Add waveform samples", "[waveform]") {
    Waveform waveform;
    
    waveform.appendSample(1000);
    waveform.appendSample(-500);
    
    REQUIRE(waveform.getNumSamples() == 2);
    REQUIRE(waveform.getSample(0) == 1000);
    REQUIRE(waveform.getSample(1) == -500);
}