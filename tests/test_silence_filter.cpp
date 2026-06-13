#include <catch2/catch_test_macros.hpp>
#include "filters/silence_filter.h"
#include "waveform.h"

TEST_CASE("SilenceFilter inserts silence in seconds", "[silence]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(1000);
    for (size_t i = 0; i < 1000; ++i) waveform.setSample(i, 100);

    SilenceFilter filter("sec", 0.01, 0.02);
    filter.apply(&waveform);
    REQUIRE(waveform.getSample(0) == 100);
    REQUIRE(waveform.getSample(440) == 100);
    
    REQUIRE(waveform.getSample(441) == 0);
    REQUIRE(waveform.getSample(882) == 0);
    
    REQUIRE(waveform.getSample(883) == 100);
}

TEST_CASE("SilenceFilter appends silence beyond signal end", "[silence]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    for (size_t i = 0; i < 100; ++i) waveform.setSample(i, 50);

    SilenceFilter filter("sec", 10.0, 11.0);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::ok);

    REQUIRE(waveform.getSample(0) == 50);
    REQUIRE(waveform.getSample(99) == 50);

    REQUIRE(waveform.getNumSamples() > 100);
}

TEST_CASE("SilenceFilter handles nullptr", "[silence]") {
    SilenceFilter filter("sec", 0.0, 1.0);
    REQUIRE(filter.apply(nullptr) == IFilter::State::error);
}