#include <catch2/catch_test_macros.hpp>
#include "ampl_filter.h"
#include "waveform.h"

TEST_CASE("AmplFilter multiplies samples correctly", "[ampl_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(10);
    
    for (size_t i = 0; i < 10; ++i) {
        waveform.setSample(i, 1000);
    }
    
    AmplFilter filter(0.5);
    IFilter::State state = filter.apply(&waveform);
    
    REQUIRE(state == IFilter::State::ok);
    
    REQUIRE(waveform.getSample(0) == 500);
    REQUIRE(waveform.getSample(9) == 500);
}

TEST_CASE("AmplFilter handles clipping", "[ampl_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(1);
    waveform.setSample(0, 30000);
    
    AmplFilter filter(2.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getSample(0) == 32767);
}

TEST_CASE("AmplFilter handles negative clipping", "[ampl_filter]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(1);
    waveform.setSample(0, -30000);
    
    AmplFilter filter(2.0);
    filter.apply(&waveform);

    REQUIRE(waveform.getSample(0) == -32768);
}

TEST_CASE("AmplFilter handles error", "[ampl_filter]") {
    AmplFilter filter(0.5);
    IFilter::State state = filter.apply(nullptr);
    REQUIRE(state == IFilter::State::error);
}

TEST_CASE("AmplFilter getter returns correct value", "[ampl_filter]") {
    AmplFilter filter(0.75);
    REQUIRE(filter.getAmpl() == 0.75);
}