#include <catch2/catch_test_macros.hpp>
#include "silence_filter.h"
#include "waveform.h"

TEST_CASE("SilenceFilter mutes specific segment", "[silence_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(1000);
    for (size_t i = 0; i < 1000; ++i) waveform.setSample(i, 100);

    SilenceFilter filter(0.01, 0.01); // 441 sample start, 441 duration
    filter.apply(&waveform);

    REQUIRE(waveform.getSample(0) == 100);
    REQUIRE(waveform.getSample(440) == 100);
    
    REQUIRE(waveform.getSample(441) == 0);
    REQUIRE(waveform.getSample(800) == 0);
    
    REQUIRE(waveform.getSample(882) == 100);
}

TEST_CASE("SilenceFilter handles out of bounds", "[silence_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(100);
    for (size_t i = 0; i < 100; ++i) waveform.setSample(i, 50);

    SilenceFilter filter(10.0, 1.0);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::ok);
    REQUIRE(waveform.getSample(0) == 50);
}

TEST_CASE("SilenceFilter handles nullptr", "[silence_filter]") {
    SilenceFilter filter(0.0, 1.0);
    REQUIRE(filter.apply(nullptr) == IFilter::State::error);
}