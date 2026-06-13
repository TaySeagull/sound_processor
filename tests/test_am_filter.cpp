#include <catch2/catch_test_macros.hpp>
#include "am_filter.h"
#include "waveform.h"

TEST_CASE("AmplitudeModulationFilter generates correct duration", "[am_filter]") {
    Waveform waveform(44100, 1, 16);

    AmplitudeModulationFilter filter(0.5, 440.0, 5.0, 1.0, 1000.0);

    filter.apply(&waveform);
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("AmplitudeModulationFilter handles nullptr", "[am_filter]") {
    AmplitudeModulationFilter filter(0.5, 440.0, 5.0, 1.0, 100.0);
    REQUIRE(filter.apply(nullptr) == IFilter::State::error);
}