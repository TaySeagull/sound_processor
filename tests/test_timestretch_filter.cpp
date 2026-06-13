#include <catch2/catch_test_macros.hpp>
#include "timestretch_filter.h"
#include "waveform.h"

TEST_CASE("TimestretchFilter speeds audio", "[timestretch_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(1000);
    
    for (size_t i = 0; i < 1000; ++i) {
        waveform.setSample(i, static_cast<int16_t>(i));
    }
    
    TimestretchFilter filter(2.0);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::ok);
    REQUIRE(waveform.getNumSamples() == 500);
}

TEST_CASE("TimestretchFilter slows down audio", "[timestretch_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);

    TimestretchFilter filter(0.5);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 200);
}

TEST_CASE("TimestretchFilter returns error for invalid factor", "[timestretch_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    
    TimestretchFilter filter(0.0);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::error);
}

TEST_CASE("TimestretchFilter getter returns correct value", "[timestretch_filter]") {
    TimestretchFilter filter(1.5);
    REQUIRE(filter.getFactor() == 1.5);
}