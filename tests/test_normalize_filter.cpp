#include <catch2/catch_test_macros.hpp>
#include "filters/normalize_filter.h"
#include "waveform.h"


TEST_CASE("NormalizeFilter scales signal to target peak", "[normalize]") {
    Waveform waveform(44100, 1, 16);

    waveform.resize(3);
    waveform.setSample(0, 1000);
    waveform.setSample(1, -2000);
    waveform.setSample(2, 500);

    NormalizeFilter filter(0.5); // 0.5 * 32767 = 16383.5
    filter.apply(&waveform);

    // scale = 16383.5 / 2000 = 8.19175
    // s[1] = -2000 * 8.19175 = -16383.5 -> -16383 or -16384
    int16_t absVal = std::abs(waveform.getSample(1));
    REQUIRE(absVal >= 16383);
    REQUIRE(absVal <= 16384);
}

TEST_CASE("NormalizeFilter handles silent signal", "[normalize]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(10);

    NormalizeFilter filter(1.0);
    filter.apply(&waveform);

    for (size_t i = 0; i < 10; ++i) {
        REQUIRE(waveform.getSample(i) == 0);
    }
}

TEST_CASE("NormalizeFilter uses default peak 1.0", "[normalize]") {
    NormalizeFilter filter;
    REQUIRE(filter.getPeak() == 1.0);
}