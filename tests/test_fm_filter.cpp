#include <catch2/catch_test_macros.hpp>
#include "fm_filter.h"
#include "waveform.h"

TEST_CASE("FrequencyModulationFilter generates correct duration", "[fm_filter]") {
    Waveform waveform(44100, 1, 16);
    FrequencyModulationFilter filter(0.5, 440.0, 110.0, 2.0, 500.0);
    filter.apply(&waveform);
    REQUIRE(waveform.getNumSamples() == 22050);
}

TEST_CASE("FrequencyModulationFilter handles nullptr", "[fm_filter]") {
    FrequencyModulationFilter filter(0.5, 440.0, 110.0, 2.0, 100.0);
    REQUIRE(filter.apply(nullptr) == IFilter::State::error);
}