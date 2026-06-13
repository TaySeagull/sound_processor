#include <catch2/catch_test_macros.hpp>
#include "filters/generator_filter.h"
#include "waveform.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

TEST_CASE("Generator sin creates correct duration", "[generator][sin]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("sin", 1.0, 440.0, 0.0, 0.0, 1000.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("Generator sin starts at zero", "[generator][sin]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("sin", 1.0, 440.0, 0.0, 0.0, 100.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getSample(0) == 0);
}

TEST_CASE("Generator sin produces correct amplitude", "[generator][sin]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("sin", 1.0, 440.0, 0.0, 0.0, 100.0);
    filter.apply(&waveform);
    
    int16_t maxVal = 0;
    for (size_t i = 0; i < waveform.getNumSamples(); ++i) {
        int16_t absVal = std::abs(waveform.getSample(i));
        if (absVal > maxVal) maxVal = absVal;
    }

    REQUIRE(maxVal >= 32760);
    REQUIRE(maxVal <= 32767);
}


TEST_CASE("Generator am creates correct duration", "[generator][am]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("am", 0.8, 440.0, 5.0, 1.0, 1000.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("Generator am starts at zero", "[generator][am]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("am", 0.8, 440.0, 5.0, 1.0, 100.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getSample(0) == 0);
}

TEST_CASE("Generator am envelope modulates correctly", "[generator][am]") {
    Waveform waveform(44100, 1, 16);
    
    // Max sample should be around 0.5 * 32767 * 2.0 = 32767
    GeneratorFilter filter("am", 0.5, 440.0, 5.0, 1.0, 1000.0);
    filter.apply(&waveform);
    
    int16_t maxVal = 0;
    for (size_t i = 0; i < waveform.getNumSamples(); ++i) {
        int16_t absVal = std::abs(waveform.getSample(i));
        if (absVal > maxVal) maxVal = absVal;
    }
    
    REQUIRE(maxVal >= 32760);
}

TEST_CASE("Generator fm creates correct duration", "[generator][fm]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("fm", 0.8, 440.0, 110.0, 200.0, 1000.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("Generator fm starts at zero", "[generator][fm]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("fm", 0.8, 440.0, 110.0, 200.0, 100.0);
    filter.apply(&waveform);
    
    REQUIRE(waveform.getSample(0) == 0);
}

TEST_CASE("Generator fm produces correct amplitude", "[generator][fm]") {
    Waveform waveform(44100, 1, 16);
    
    GeneratorFilter filter("fm", 1.0, 440.0, 110.0, 200.0, 100.0);
    filter.apply(&waveform);
    
    int16_t maxVal = 0;
    for (size_t i = 0; i < waveform.getNumSamples(); ++i) {
        int16_t absVal = std::abs(waveform.getSample(i));
        if (absVal > maxVal) maxVal = absVal;
    }
    
    REQUIRE(maxVal >= 32760);
    REQUIRE(maxVal <= 32767);
}