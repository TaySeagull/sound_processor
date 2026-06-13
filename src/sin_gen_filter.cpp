#include "sin_gen_filter.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

/**
 * @brief Constuctor for SinGenFilter
 */
SinGenFilter::SinGenFilter(double ampl, double freqHz, double durationMs)
    : ampl_(ampl), freq_(freqHz), duration_(durationMs) {}

/**
 * @brief Applies SinGenFilter
 */
IFilter::State SinGenFilter::apply(Waveform* sound) {
    if (!sound) {
        return State::error;
    }

    uint32_t sampleRate = sound->getSampleRate();
    size_t samplesNumber = static_cast<size_t>((duration_ / 1000.0) * sampleRate);
    
    sound->clear();
    sound->resize(samplesNumber);
    
    std::vector<int16_t>& samples = sound->getSamples();

    double maxAmpl = 32767.0 * ampl_;
    double angularFreq = 2.0 * PI * freq_ / sampleRate;
    
    for (size_t i = 0; i < samplesNumber; ++i) {
        double val = maxAmpl * std::sin(angularFreq * i);
        samples[i] = static_cast<int16_t>(val);
    }
    
    return State::ok;
}