#include <catch2/catch_test_macros.hpp>
#include "filters/timestretch_filter.h"
#include "waveform.h"

TEST_CASE("TimestretchFilter stretches signal ", "[timestretch]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    for (size_t i = 0; i < 100; ++i) waveform.setSample(i, static_cast<int16_t>(i));
    
    TimestretchFilter filter(2.0);
    filter.apply(&waveform);
    
    // newSize = round(100 * 2) = 200
    REQUIRE(waveform.getNumSamples() == 200);
}

TEST_CASE("TimestretchFilter compresses signal", "[timestretch]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    
    TimestretchFilter filter(0.5);
    filter.apply(&waveform);
    
    // newSize = round(100 * 0.5) = 50
    REQUIRE(waveform.getNumSamples() == 50);
}

TEST_CASE("TimestretchFilter preserves first sample", "[timestretch]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    waveform.setSample(0, 1234);
    
    TimestretchFilter filter(2.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getSample(0) == 1234);
}