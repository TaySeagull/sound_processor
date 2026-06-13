#include <catch2/catch_test_macros.hpp>
#include "filters/lowpass_filter.h"
#include "waveform.h"

TEST_CASE("LowpassFilter smooths sharp transition", "[lowpass]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(5);

    waveform.setSample(2, 10000);

    LowpassFilter filter(3);
    filter.apply(&waveform);

    REQUIRE(waveform.getSample(2) == 3333);
    
    REQUIRE(waveform.getSample(1) == 3333);
    REQUIRE(waveform.getSample(3) == 3333);
}

TEST_CASE("LowpassFilter handles edges", "[lowpass]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(3);
    waveform.setSample(0, 1000);
    waveform.setSample(1, 2000);
    waveform.setSample(2, 3000);

    LowpassFilter filter(3);
    filter.apply(&waveform);

    // Index 0: window is [-1, 0, 1] -> clamped to [0, 0, 1] -> [1000, 1000, 2000]
    // 4000 / 3 = 1333
    REQUIRE(waveform.getSample(0) == 1333);
}