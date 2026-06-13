#include <catch2/catch_test_macros.hpp>
#include "sin_gen_filter.h"
#include "waveform.h"
#include <cmath>

TEST_CASE("SinGenFilter generates correct number of samples", "[sin_gen_filter]") {
    Waveform waveform(44100, 1, 16);

    SinGenFilter filter(1.0, 440.0, 1000.0);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::ok);
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("SinGenFilter replaces existing waveform data", "[sin_gen_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    waveform.setSample(0, 999);
    
    SinGenFilter filter(0.5, 440.0, 10.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 441);
    REQUIRE(waveform.getSample(0) == 0);
}

TEST_CASE("SinGenFilter handles different durations", "[sin_gen_filter]") {
    Waveform waveform(44100, 1, 16);
    

    SinGenFilter filter(1.0, 440.0, 500.0);
    filter.apply(&waveform);
    
    // 0.5 * 44100 = 22050
    REQUIRE(waveform.getNumSamples() == 22050);
}

TEST_CASE("SinGenFilter handles nullptr", "[sin_gen_filter]") {
    SinGenFilter filter(1.0, 440.0, 100.0);
    IFilter::State state = filter.apply(nullptr);
    REQUIRE(state == IFilter::State::error);
}

TEST_CASE("SinGenFilter getters return correct values", "[sin_gen_filter]") {
    SinGenFilter filter(0.8, 880.0, 250.0);
    
    REQUIRE(filter.getAmpl() == 0.8);
    REQUIRE(filter.getFreqHz() == 880.0);
    REQUIRE(filter.getDurationMs() == 250.0);
}